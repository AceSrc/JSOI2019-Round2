#! /usr/bin/env python
import yaml
import subprocess
from random import randint
import random

def compile():
    sp = subprocess.Popen(["g++", "std/std.cpp", "-fsanitize=undefined", "-fsanitize=address", "-std=c++11", "-Wall", "-o", "std/std"]) 
    sp.communicate()
    assert sp.returncode == 0

def run(cases):
    sp = subprocess.Popen(["std/std < data/%d.in > data/%d.ans" % (cases, cases)], shell=True)
    sp.communicate()
    assert sp.returncode == 0

if __name__ == '__main__':
    compile()
    for i in range(1, 23):
        sp = subprocess.Popen(["./mk data/%d.in %d" % (i, i)], shell=True)
        sp.communicate()
        assert sp.returncode == 0
        run(i)
        print('testcases %d finished' % (i))
