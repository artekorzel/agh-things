import sys
from typy import kubelki1

def sortuj(args):
    for s in args:
        i=int(float(s)*10)
        kubelki1[i].append(float(s))       
    for k in range(len(kubelki1)):
        kubelki1[k].sort()

def wypisz():
    for i in kubelki1:
        print i
    for i in kubelki1:
    	for j in i: 
    		print j

