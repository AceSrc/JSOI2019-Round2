#! /usr/bin/env python
import yaml
import subprocess
from random import randint

def compile():
    sp = subprocess.Popen(["g++", "std/std.cpp", "-fsanitize=undefined", "-fsanitize=address", "-std=c++11", "-Wall", "-o", "std/std"]) 
    sp.communicate()
    assert sp.returncode == 0

def run(cases):
    sp = subprocess.Popen(["std/std < data/%d.in > data/%d.ans" % (cases, cases)], shell=True)
    sp.communicate()
    assert sp.returncode == 0

def gencases(cases, args, fd):
    if cases == 1:
        fd.write('3\n1 2 3\n')
        return 
    (n, upper) = tuple(args)
    fd.write("%d\n" % (n))
    for i in range(n):
        if i == n - 1: fd.write('%d\n' % (randint(0, upper)))
        else: fd.write('%d ' % (randint(0, upper)))

def fib(n):
    f = ['a', 'b']
    fib = [1, 1]
    for i in range(2, n):
        if fib[i - 1] + fib[i - 2] > n:
            rt = f[i - 1]
            return (rt, fib[i - 1])
        f.append(f[i - 2] + f[i - 1]);
        fib.append(fib[i - 2] + fib[i - 1])

def repeat(s, k):
    rt = ""
    for i in range(k):
        rt += s
    return rt

def randstr(n, cset):
    rt = ""
    for i in range(n):
        rt += cset[ randint(0, len(cset) - 1) ] 
    return rt


def longstr(a, b, k):
    return a + repeat(b, k - 1)

def algo0(n, rand_len, pqqq_len, pqqq_times, ab_len):
    assert rand_len + pqqq_len * pqqq_times + ab_len * 2 < n
    rest = n - (rand_len + pqqq_len * pqqq_times + ab_len * 2)

    rt = randstr(rand_len, "wsxyz")
    rt += repeat(longstr('p', 'q', pqqq_len), pqqq_times)
    assert len(rt) == rand_len + pqqq_len * pqqq_times
    (cur, L) = fib(rest)
    rt += cur
    rt += repeat('ab', ab_len)
    rt += repeat('a', rest - L)
    return rt;

def algo1(n, rand_len, k, unit_len):
    candy = [randstr(randint(0, unit_len - 1), "ab") + 'b' for i in range(k)] 
    rt = randstr(rand_len, "wsxyz") 
    for i in range(k):
        rest = n - len(rt)
        upper = rest // len(candy[i])
        times = randint(upper // 2, upper)
        rt += repeat(candy[i], times)
    rest = n - len(rt)
    (cur, L) = fib(rest)
    rt += cur + repeat('a', rest - L)
    return rt

def algo2(n, gap):
    assert 26 * 25 * gap <= n
    rest = n - 26 * 25 * gap
    rt = "" 
    for i in range(25, 0, -1):
        for j in range(26, i, -1):
            rt = rt + repeat(chr(ord('a') + i - 1) + chr(ord('a') + j - 1), gap)
    assert len(rt) + rest == n
    rt = rt + repeat('a', rest)
    return rt

def gen(cases, n, is_sample=False):
    with open('data/%d.in' % cases, 'w')  as fd:
        rt = "" 
        if cases == 10:
            rt = algo0(n, 100000, 200, 2000, 100000)
        if cases == 9:
            rt = algo0(n, 100000, 200, 2000, 200000)
        if cases == 8:
            rt = algo0(n, 100000, 50, 10000, 100000)
        if cases == 7:
            rt = algo0(n, 20000, 5, 2000, 10000)
        if cases == 6:
            rt = algo1(n, 100000, 4, 1000)
        if cases == 5:
            rt = algo2(n, 300)
        if cases >= 2 and cases <= 4:
            rt = randstr(n, 'abc')
        if cases == 1:
            rt = 'caccabbbaa'
        if cases == 0:
            rt = randstr(n, 'abc')
        assert(len(rt) == n)
        fd.write("%s\n" % rt)
    run(cases)

if __name__ == '__main__':
    compile()
    gen(0, 10)
    for i in range(1, 11):
        if i == 1: gen(i, 10)
        elif i <= 3: gen(i, 1000)
        elif i <= 7: gen(i, 200000)
        elif i <= 10: gen(i, 1000000)
        print("testcase %d finished." % i)



