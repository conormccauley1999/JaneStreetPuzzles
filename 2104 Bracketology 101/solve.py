import decimal
from copy import deepcopy

decimal.getcontext().prec = 10
D = decimal.Decimal

px = lambda x, y: D(y) / (D(x) + D(y))
py = lambda x, y: D(x) / (D(x) + D(y))

T = D(0)

def pwin(B, P=D(1)):
    if 2 not in B: return
    S = len(B) // 2
    if not S:
        global T
        T += P
        return
    b = [0] * S
    for r in range(pow(2, S)):
        p = P
        for i in range(S):
            x, y = B[(i * 2) + 1], B[i * 2]
            if (r >> i) & 1:
                p *= px(x, y)
                b[i] = x
            else:
                p *= py(x, y)
                b[i] = y
        pwin(b, p)

def solve():
    global T
    B = [1, 16, 8, 9, 5, 12, 4, 13, 6, 11, 3, 14, 7, 10, 2, 15]
    pwin(B)
    I = T
    mx = T
    mi = mj = -1
    for i in range(16):
        for j in range(16):
            if i == j: continue
            b = deepcopy(B)
            T = D(0)
            b[i], b[j] = b[j], b[i]
            pwin(b)
            if T > mx:
                mx = T
                mi, mj = B[i], B[j]
    print(f'Init = {I}')
    print(f'Best = {mx}')
    print(f'Incr = {mx - I}')
    print(f'Swap = ({mi}, {mj})')

solve()
