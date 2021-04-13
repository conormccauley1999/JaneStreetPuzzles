from collections import Counter
from math import factorial, gcd
from string import ascii_uppercase as ALPHABET

class Base:
    def __init__(self, string):
        self.string = string
        self.counter = Counter(string)
        self.shuffles = factorial(len(string))
        self.majority = ''
        mx = 0
        for key in self.counter:
            val = self.counter[key]
            if val > mx:
                self.majority = key
                mx = val
            self.shuffles //= factorial(val)
    
    def __str__(self):
        return f'Base<{self.string}, {tuple(self.counter.values())}>' 
    
    def __hash__(self):
        return hash(self.string)

    def is_valid(self):
        values = list(self.counter.values())
        return values.count(max(values)) == 1

class Candy:
    def __init__(self, N):
        self.N = N
        self.F = factorial(N)
        self.strings = set()
        self.bases = set()
        self.combinations = set()
        self.count = 0
    
    def solve(self):
        self.generate_strings()
        print(len(self.strings))
        self.generate_bases()
        self.generate_combinations()
        total = factorial(pow(self.N, 2)) // pow(factorial(self.N), self.N)
        div = gcd(self.count, total)
        print(f'{self.count} / {total}')
        print(f'{self.count // div} / {total // div}')
        print(self.count / total)

    def generate_combinations(self, bases=set(), counter=Counter(), majorities=set()):
        if len(bases) == self.N:
            fset = frozenset(bases)
            if fset not in self.combinations:
                self.combinations.add(fset)
                new = self.F
                for base in bases: new *= base.shuffles
                self.count += new
        for base in self.bases - bases:
            if base.majority in majorities: continue
            new_counter = counter + base.counter
            if max(list(new_counter.values())) > self.N: continue
            new_majorities = majorities | {base.majority}
            new_bases = bases | {base}
            self.generate_combinations(bases=new_bases, counter=new_counter, majorities=new_majorities)
    
    def generate_bases(self):
        for string in sorted(self.strings):
            base = Base(string)
            if base.is_valid():
                self.bases.add(base)

    def generate_strings(self, string='', index=0):
        if len(string) == self.N:
            self.strings.add(string)
            return
        for i in range(index, self.N):
            self.generate_strings(string=string + ALPHABET[i], index=i)

def test():
    for n in range(2, 6):
        print(f'N = {n}')
        candy = Candy(n)
        candy.solve()
        print()

test()
