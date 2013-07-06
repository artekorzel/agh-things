#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import getopt

def wypisz(args):
    if type(args)==list:
        print 'Dlugosc najdluzszego argumentu:'
    	najdl=0
    	for s in args:
            if len(s)>najdl:
                najdl=len(s)
    	print najdl
    else:
    	print 'Blad! Podany argument nie jest lista'
    
if __name__=='__main__':
    wypisz(sys.argv[1:])
else:
    wypisz(['jahs','dsajdhsa','fasaas'])
