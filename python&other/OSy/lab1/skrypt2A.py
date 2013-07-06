#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys

def wypisz(args):
    print "Liczba argumentow:",len(args)
    najdl=0
    for s in args:
        if len(s)>najdl:
            najdl=len(s)
    print "Dlugosc najdluzszego argumentu:",najdl

wypisz(sys.argv[1:])
