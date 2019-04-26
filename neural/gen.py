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


if __name__ == '__main__':
    compile()
    for i in range(1, 3):
        infile = 'down/%d.in' % i
        outfile = 'down/%d.ans' % i
        
        with open(infile, 'w') as fd:
            if i == 1:
                fd.write('2\n')
                fd.write('3\n')
                fd.write('1 2\n')
                fd.write('1 3\n')
                fd.write('2\n')
                fd.write('1 2\n')
            elif i == 2:
                fd.write('3\n')
                fd.write('3\n')
                fd.write('1 2\n')
                fd.write('1 3\n')
                fd.write('4\n')
                fd.write('1 2\n')
                fd.write('2 3\n')
                fd.write('3 4\n')
                fd.write('2\n')
                fd.write('1 2\n')

        run(i, infile, outfile)
        print('sample %d finished' % (i))

    for i in range(1, 21):
        infile = 'data/%d.in' % i
        outfile = 'data/%d.ans' % i
        sp = subprocess.Popen(["./mk data/%d.in %d" % (i, i)], shell=True)
        sp.communicate()
        assert sp.returncode == 0
        run(i, infile, outfile)
        print('testcases %d finished' % (i))
