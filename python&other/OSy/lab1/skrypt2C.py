#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import getopt

def wypisz(opcja, args):
    if type(args)==list:
    	if opcja=='-p' or opcja=='--palindrom':
                print "Palindromy:"
    		for s in args:
    			if s==s[::-1]:
    				print s
    	elif opcja=='-m' or opcja=='--max':
                print 'Dlugosc najdluzszego argumentu:'
    		najdl=0
    		for s in args:
    			if len(s)>najdl:
    				najdl=len(s)
    		print najdl
    	elif opcja=='-h' or opcja=='--help':
    		print 'Uzycie: program [opcje] [ciag wyrazow oddzielonych spacjami]'
    	else:
    		print 'Blad! Sprobuj: "program --help" zeby uzyskac pomoc'
    else:
    	print 'Blad! Podany argument nie jest lista'
    
if __name__=='__main__':
    opcje,argumenty=getopt.getopt(sys.argv[1:],'pmh',['palindrom','max','help'])
    for o in opcje:
        wypisz(o[0],argumenty)
