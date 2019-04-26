#! /usr/bin/env python
import yaml
import subprocess
from random import randint
import random

def compile():
    sp = subprocess.Popen(["g++", "std/std.cpp", "-fsanitize=undefined", "-fsanitize=address", "-std=c++11", "-Wall", "-o", "std/std"]) 
    sp.communicate()
    assert sp.returncode == 0

def run(cases, infile, outfile):
    sp = subprocess.Popen(["std/std < %s > %s" % (infile, outfile)], shell=True)
    sp.communicate()
    assert sp.returncode == 0

def rand_edge(fd, T, n, m):
    for i in range(m):
        fd.write("%d %d %d %d\n" % (randint(0, 1), randint(1, T - 1), randint(1, n), randint(1, n)))

def gen_random(T, n, m, fd):
    for _ in range(m):
        action = randint(0, 1)
        if action == 0:
            t, x, y = randint(1, T - 1), randint(1, n), randint(1, n)
            fd.write("%d %d %d %d\n" % (action, t, x, y)) 
        else:
            t, x, y = randint(1, T), randint(1, n), randint(1, n)
            fd.write("%d %d %d %d\n" % (action, t, x, y)) 

def sub_hack_bfs(T, n, m, fd, delta, time_offset=0):
    assert n == m
    fd.write("%d %d %d %d\n" % (1, 1 + time_offset, delta + 1, delta + 1))
    for i in range(2, n + 1):
        fd.write("%d %d %d %d\n" % (0, i // 2 + time_offset, delta + (i // 2) * 2 - 1, delta + i))

def hack_bfs(T, n, m, fd):
    assert n % 2 == 0
    sub_hack_bfs(T, n // 2, n // 2, fd, 0)
    sub_hack_bfs(T, n // 2, n // 2, fd, n / 2)
    rand_edge(fd, T, n, m - n)

def gen_layers(fd, T, n, m, start_size, layer_size, P, Q):
    assert m // 2 == n
    assert start_size < n
    datalist = [i + 1 for i in range(n)]
    random.shuffle(datalist)
    gp = []
    v = randint(1, start_size)
    for i in range(v):
        gp.append(datalist[i])

    for i in range(T - 1, 1, -3):
        if n == v: break
        _T = v + randint(1, min(layer_size, n - v))
        for j in range(v, _T):
            fd.write("%d %d %d %d\n" % (0, i, datalist[j], gp[ randint(0, len(gp) - 1) ]))
            m -= 1
            if randint(1, P) <= Q: 
                fd.write("%d %d %d %d\n" % (1, i - 1, datalist[j], randint(1, n)))
                m -= 1
        gp = []
        for j in range(v, _T):
            gp.append(datalist[j])
        v = _T
    rand_edge(fd, T, n, m)

def two_layers(fd, T, n, m):
    assert m == 2 * n 
    assert n % 2 == 0
    datalist = [i + 1 for i in range(n)]
    random.shuffle(datalist)
    for i in range(1, n + 1):
        m -= 1
        fd.write("%d %d %d %d\n" % (0, 1, i, datalist[i - 1]))
     
    datalist = [i + 1 for i in range(n // 2)]
    random.shuffle(datalist)
    for i in range(n // 2 + 1, n + 1):
        m -= 1
        fd.write("%d %d %d %d\n" % (1, 1, i, datalist[i - 1 - n // 2]))
    sub_hack_bfs(T, n // 2, m, fd, n // 2, T // 2)
     

def gen(cases, T, n, m, algo, is_sample=False):
    infile = "data/%d.in" % cases if not is_sample else "down/%d.in" % cases
    outfile = "data/%d.ans" % cases if not is_sample else "down/%d.ans" % cases
    with open(infile, 'w')  as fd:
        fd.write("%d %d %d\n" % (T, n, m)) 
        if cases == 1 and is_sample:
            fd.write("0 2 1 3\n1 1 2 3\n") 
        elif algo == 0:
            gen_random(T, n, m, fd)
        elif algo == 1:
            hack_bfs(T, n, m, fd)
        elif algo == 2:
            gen_layers(fd, T, n, m, 100, 8, 1, 1)
        elif algo == 3:
            two_layers(fd, T, n, m)
    run(cases, infile, outfile)

if __name__ == '__main__':
    compile()
    # gen(0, 3, 4, 8, 0)
    for i in range(1, 3):
        if i == 1: gen(i, 3, 3, 2, 0, True) 
        if i == 2: gen(i, 10, 10, 20, 0, True) 
        print("finished sample %d" % i)

    for i in range(1, 11):
        if i == 1: gen(i, 2, 10, 10, 0)
        elif i <= 3: gen(i, 100, 100, 200, 0)
        elif i == 4: gen(i, 1000000, 3000, 6000, 3)
        elif i == 5: gen(i, 40000, 10000, 20000, 1)
        elif i == 6: gen(i, 40000, 10000, 20000, 2)
        elif i == 7: gen(i, 1000000, 30000, 60000, 2)
        elif i == 8: gen(i, 1000000, 40000, 80000, 1)
        elif i == 9: gen(i, 1000000, 50000, 100000, 2)
        elif i == 10: gen(i, 1000000, 50000, 100000, 3)
        print("finished testcase %d" % i)
    
    # for i in range(1, 201):
        # T = randint(2, 10)
        # n = randint(1, 10)
        # m = randint(1, 30)
        # gen(i, T, n, m, 0)
        # print("finished %d" % i)

    # for i in range(1, 21):
        # gen(i, 1000000, 10000, 20000, 1)
        # print("testcase %d finished." % i)
    # for i in range(1, 6):
        # gen(i, 1000000, 50000, 100000, 0)
        # print("testcase %d finished." % i)
    # for i in range(6, 11):
        # gen(i, 1000000, 50000, 100000, 1)
        # print("testcase %d finished." % i)
    # for i in range(11, 16):
        # gen(i, 1000000, 50000, 100000, 2)
        # print("testcase %d finished." % i)
    # for i in range(16, 21):
        # gen(i, 1000000, 50000, 100000, 3)
        # print("testcase %d finished." % i)
