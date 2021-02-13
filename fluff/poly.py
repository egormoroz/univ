import numpy as np

def ordered(a, b):
    if len(a) >= len(b):
        return (a, b)
    return (b, a)

def eqlz(a, b):
    a, b = ordered(a, b)
    n = len(a) - len(b)
    b[:n] = [0] * n
    return (a, b)

def trim(a):
    k = (a != 0).argmax()
    return a[k:] if a[k] != 0 else np.array([], dtype='int32')

def pdiv(a, b):
    a, b = np.array(a), np.array(b)
    q = [0] * (len(a) - len(b) + 1)
    d = b[0] ** len(q)
    r = a * d
    while len(r) >= len(b):
        assert(r[0] % b[0] == 0)
        k = r[0] // b[0]
        q[len(r) - len(b)] = k
        r[:len(b)] -= b * k
        r = trim(r)
    return (np.array(list(reversed(q))), r, d)

def gcd(a, b):
    r = pdiv(a, b)[1]
    return b if len(r) == 0 else gcd(b, r)

def simplify(a):
    from math import gcd
    d = a[0]
    for i in a:
        d = gcd(d, i)
    return a // (-d) if a[0] < 0 else a // d

def mul(a, b):
    c = np.array([0] * (len(a) + len(b) - 1))
    for i in range(len(a)):
        for j in range(len(b)):
            c[i + j] += a[i] * b[j]
    return trim(c)

def polyrepr(a):
    dg = len(a) - 1
    if not len(a):
        return ''
    if dg == 0:
        return str(a[0])
    text = ''
    def f(n, b=False):
        if n == 1:
            return '+' if b else ''
        elif n == -1:
            return '-'
        return f'+{n}' if b and n > 0 else str(n)
    if dg > 1:
        text = f'{f(a[0])}x^{dg}'
    for i, k in enumerate(a[1:-2]):
        if k == 0:
            continue
        text += f'{f(k,True)}x^{dg - i}'
    if dg > 1 and a[-2] > 0:
        text += '+'
    if a[-2]:
        text += f'{f(a[-2])}x'
    if (a[-2] or dg > 1) and a[-1] > 0:
        text += '+'
    if a[-1]:
        text += f'{a[-1]}'
    return text

def pprint(a):
    print(polyrepr(simplify(trim(a))))

def pprintraw(a):
    print(polyrepr(trim(a)))

