import sys
from typy import kubelki2

def sortuj(args):
    for s in args:
        i=int(float(s)*10)
        if i not in kubelki2:
            nowyKubelek=list()
            kubelki2[i]=nowyKubelek
        kubelki2[i].append(float(s))       
    for k in kubelki2:
        kubelki2[k].sort()

def wypisz():
    for i in kubelki2:
        print kubelki2[i]
    klucze=kubelki2.keys()
    klucze.sort()
    for i in klucze:
    	for j in kubelki2[i]:
    		print j

