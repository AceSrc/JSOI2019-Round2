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
    (m,) = readint(fi)
    if args['m'] < 0:
        assert m == -args['m']
    else:
        assert 1 <= m and m <= args['m']
    tot = 0
    for i in range(m):
        (k,) = readint(fi)
        if args['k'] < 0: 
            assert k == -args['k']
        elif args['k'] > 0:
            assert k <= args['k']
        for i in range(1, k):
            (x, y) = readint(fi)
            assert 1 <= x and x <= k
            assert 1 <= y and y <= k
        tot += k 
    if args['n'] < 0:
        assert tot == -args['n']
    else:
        assert tot <= args['n']

    assert not fi.readline()

def checker():
    with open('conf.yaml', 'r') as f:
        prob = yaml.load(f)['args']

    for item in prob:
        caseslist = item['cases']
        for cases in caseslist:
            log("start %d.in" % cases)
            with open('data/%d.in' % cases, 'r') as inputfile:
                check(item, inputfile)
    
    for i in range(1, 3):
        log("start sample %d.in" % i)
        with open('down/%d.in' % i, 'r') as inputfile:
            check({'k': 100, 'n': 100, 'm': 100}, inputfile)

if __name__ == '__main__':
    checker()
