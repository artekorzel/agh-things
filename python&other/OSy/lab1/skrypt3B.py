import sys
import getopt
import typy.listy
import typy.slownik

def dzialania(argument, lista_arg):
    if argument=='--lista':    	
	typy.listy.sortuj(lista_arg)
	typy.listy.wypisz()
    elif argument=='--slownik':
    	typy.slownik.sortuj(lista_arg)
    	typy.slownik.wypisz()
    else:
        print 'Blad! Zly parametr'
        
def sortujIWypisz(args):
    opcje,argumenty=getopt.getopt(args,'',['lista','slownik'])
    for o in opcje:
        dzialania(o[0],argumenty)
        
if __name__=='__main__':
    sortujIWypisz(sys.argv[1:])  

