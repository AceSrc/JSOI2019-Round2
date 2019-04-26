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
    s = readstr(fi)
    assert 1 <= len(s) and len(s) <= args['n']
    if args['is_abc']:
        for i in s:
            assert 0 <= ord(i) - ord('a') <= 2
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

if __name__ == '__main__':
    checker()
