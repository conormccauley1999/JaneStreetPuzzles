from random import shuffle
ALPH = 'ABCDE'

def mcs(k):
    candies = []
    for c in ALPH[:k]: candies.extend([c] * k)
    shuffle(candies)
    chunks = []
    for i in range(0, k*k, k): chunks.append(candies[i:i+k])
    used = set()
    for c in ALPH[:k]:
        cnts = []
        for i in range(k): cnts.append((chunks[i].count(c), i))
        cnts.sort(reverse=True)
        if cnts[0][0] <= cnts[1][0] or cnts[0][1] in used: return 0
        used.add(cnts[0][1])
    return 1

N = 1000000
for k in range(2, 6):
    print(f'{k} => {sum(mcs(k) for _ in range(N)) / N}')
