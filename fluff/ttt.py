def check(a):
    if a[4] != 0 and (a[1] == a[4] == a[7] or a[3] == a[4] == a[5] or a[0] == a[4] == a[8] or a[2] == a[4] == a[6]):
        return a[4]
    if a[0] != 0 and (a[0] == a[1] == a[2] or a[0] == a[3] == a[6]):
        return a[0]
    if a[8] != 0 and (a[6] == a[7] == a[8] or a[2] == a[5] == a[8]):
        return a[8]
    return 0


def my_print(a):
    g = lambda x: ''.join(map(lambda y: '0' if y == -1 else 'x' if y == 1 else '.', x))
    print('\n'.join([g(a[:3]), g(a[3:6]), g(a[6:])]))


a = [0] * 9
b = set([])

def f(c=True, w=1):
    r = check(a)
    if r != 0:
        return r
    h = 1 if c else -1

    p,q, l = False, True, False
    for i in range(9):
        if a[i] == 0:
            l = True
            a[i] = h
            t = f(not c, w)
            if t == w:
                p = True
            else:
                q = False
            a[i] = 0
    if not l:
        return 0
    if h == w and p or h != w and q:
        b.add(tuple(a))
        return w
    return 0


#number of move
def nom(x):
    return 9-x.count(0)    

def fastest(c=b):
    return min(c, key=nom)

def with_len(n, c=b):
    return list(filter(lambda x: nom(x) == n, c))

def variants(a, c=b):
    def fltr(x):
        for i, j in zip(a, x):
            if i != 0 and i != j: 
                return False
        return True
    return list(sorted(filter(fltr, c), key=nom))

def next_any(a, c=b):
    return variants(a, c)[1]

def next_all(a, c=b):
    return variants(a, c)[1:]

