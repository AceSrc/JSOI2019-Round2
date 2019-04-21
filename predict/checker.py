#! /usr/bin/env python
import yaml

def log(s):
    print('-- %s --' % s)

def readint(fi):
    s = fi.readline()
    return tuple(map(int, s.split(' ')))

def readstr(fi):
    return fi.readline()[0:-1]

def check(args, fi): 
    # print(readint(fi))
    (T, n, m) = readint(fi)
    assert 1 <= T and T <= args['T']
    assert 1 <= n and n <= args['n']
    assert 1 <= m and m <= args['m']
    for i in range(m):
        (action, t, x, y) = readint(fi)
        assert action == 0 or action == 1
        assert (action == 0 and t <= T - 1) or (action == 1 and t <= T)
        assert 1 <= x and x <= n
        assert 1 <= y and y <= n

def checker():
    with open('conf.yaml', 'r') as f:
        prob = yaml.load(f)['args']

    for item in prob:
        caseslist = item['cases']
        for cases in caseslist:
            log("start %d.in" % cases)
            with open('data/%d.in' % cases, 'r') as inputfile:
                check(item, inputfile)

if __name__ == '__main__':
    checker()
