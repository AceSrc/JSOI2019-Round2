#! /usr/bin/env python
import yaml
import subprocess
from random import randint

def compile():
    sp = subprocess.Popen(["g++", "std/std.cpp", "-fsanitize=undefined", "-fsanitize=address", "-std=c++11", "-Wall", "-o", "std/std"]) 
    sp.communicate()
    assert sp.returncode == 0

def run(cases, infile, outfile):
    sp = subprocess.Popen(["std/std < %s > %s" % (infile, outfile)], shell=True)
    sp.communicate()
    assert sp.returncode == 0

def repeat(s, times):
    rt = ""
    for i in range(times):
        rt += s
    return rt

def randstr(n, cset):
    rt = ""
    for i in range(n):
        rt += cset[ randint(0, len(cset) - 1) ] 
    return rt

def ch(x):
    return chr(ord('a') + x)

def palindromic(n, start_chr=0):
    rt = ch(start_chr)
    for i in range(start_chr + 1, 26):
        if len(rt) * 2 + 1 > n: break
        rt = rt + ch(i) + rt 
    return rt

def fib(n, start_chr=0):
    assert 0 <= start_chr <= 24
    f = [ch(start_chr), ch(start_chr + 1)]
    for i in range(2, 10000):
        if len(f[i - 2]) + len(f[i - 1]) > n:
            return f[i - 1]
        f.append(f[i - 2] + f[i - 1])

def algo0(n, rand_len, period_len, times, C):
    assert rand_len + period_len * times < n
    rt = repeat(palindromic(63, ord('t') - ord('a')), 1000) # 63500
    rt += randstr(rand_len, "stu")
    for i in range(15, (15 - 2 * C), -2): # uv, tu, st...
        T = randint(50, period_len)
        G = period_len * times // T
        rt = rt + repeat(randstr(T, [ch(i), ch(i + 1)]), G)
    rt += fib(n - len(rt), 1) 
    rt += palindromic(n - len(rt))
    rt += randstr(n - len(rt), 'ab')
    return rt;

def all_stars(n, gap):
    # yzyzyzyzyz...xzxzxzxz....xyxyxy.... 
    assert 26 * 25 * gap <= n
    rt = "" 
    for i in range(25, 0, -1):
        for j in range(26, i, -1):
            rt = rt + repeat(ch(i - 1) + ch(j - 1), gap)
    rt = rt + randstr(n - len(rt), 'ab')
    return rt

def mainly_palindromic(n):
    # mainly palindromic 
    rt = palindromic(n // 2, 3)
    m = (n - len(rt)) // 3
    rt = rt + repeat(randstr(50, 'ca'), m // 50)
    rt = rt + randstr(n - len(rt), 'ab')
    return rt

def gen(cases, n, is_sample=False):
    infile = 'data/%d.in' % cases
    outfile = 'data/%d.ans' % cases
    if is_sample:
        infile = 'down/%d.in' % cases
        outfile = 'down/%d.ans' % cases

    with open(infile, 'w')  as fd:
        rt = "" 
        if is_sample:
            rt = randstr(n, 'abc')
        elif cases == 10:
            rt = repeat(palindromic(127, ord('s') - ord('a')), 1000) # 63500
            rt += randstr(100000, 'st')
            rt += fib(75025, ord('q') - ord('a'))
            rt += repeat(palindromic(511, ord('i') - ord('a')), 200)
            rt += repeat('gh', 50000)
            rt += repeat(randstr(50, 'fg'), 2000) 
            rt += repeat(randstr(100, 'ef'), 2000) 
            rt += randstr(100000, 'abc') 
            rt += randstr(n - len(rt), 'ab')
        elif cases == 9:
            cur = palindromic(511)
            rt = repeat(cur, 1000000 / 511)
            rt = rt + randstr(n - len(rt), 'ab')
            # cur = palindromic(127)
            # rt = repeat(palindromic(127), 500)
        elif cases == 8:
            rt = repeat(palindromic(127, ord('s') - ord('a')), 3000) # 63500
            rt += repeat("rs", 50000) 
            rt += repeat(fib(233, ord('q') - ord('a')), 2000) 
            rt += repeat('a', n - len(rt))

        elif cases == 7:
            rt = repeat(palindromic(127, ord('s') - ord('a')), 1000) # 63500
            rt += repeat(fib(610, ord('r') - ord('a')), 500) # 368500
            rt += repeat(randstr(50, 'rs'), 2000) # 468500
            rt += repeat('p' + repeat('p', 232), 500)
            rt += repeat(randstr(50, 'pq'), 500)
            rt += randstr(200000, 'opq')
            rt += repeat('fg', 50000)
            rt += repeat('eeeddd', 2000)
            rt += randstr(n - len(rt), 'ab')
        elif cases == 6:
            rt = algo0(n, 100000, 200, 1000, 4)
        elif cases == 5:
            rt = all_stars(n, n // (26 * 25))
        elif cases >= 2 and cases <= 4:
            rt = randstr(n, 'abc')
        elif cases == 1:
            rt = 'caccabbbaa'
        elif cases == 0:
            rt = randstr(n, 'abc')

        assert(len(rt) == n)
        fd.write("%s\n" % rt)
    run(cases, infile, outfile)

if __name__ == '__main__':
    compile()
    gen(1, 10, is_sample=True)
    gen(2, 100, is_sample=True)
    print('sample finished. ')
    for i in range(1, 11):
        if i == 1: gen(i, 10)
        elif i <= 3: gen(i, 1000)
        elif i == 4: gen(i, 200000)
        elif i == 5: gen(i, 50000)
        elif i <= 10: gen(i, 1000000)
        print("testcase %d finished." % i)



