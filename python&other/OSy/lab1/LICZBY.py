# -*- coding: utf-8 -*-

import sys

cyf={0:"",
     1:"jeden",
     2:"dwa",
     3:"trzy",
     4:"cztery",
     5:"pięć",
     6:"sześć",
     7:"siedem",
     8:"osiem",
     9:"dziewięć"}
nast={10:"dziesięć",
      11:"jedenaście",
      12:"dwanaście",
      13:"trzynaście",
      14:"czternaście",
      15:"piętnaście",
      16:"szesnaście",
      17:"siedemnaście",
      18:"osiemnaście",
      19:"dziewiętnaście"}
dzies={0:"",
       2:"dwadzieścia",
       3:"trzydzieści",
       4:"czterdzieści",
       5:"pięćdziesiąt",
       6:"sześćdziesiąt",
       7:"siedemdziesiąt",
       8:"osiemdziesiąt",
       9:"dziewięćdziesiąt"}
sety={0:"",
      1:"sto",
      2:"dwieście",
      3:"trzysta",
      4:"czterysta",
      5:"pięćset",
      6:"sześćset",
      7:"siedemset",
      8:"osiemset",
      9:"dziewięćset"}

def nazwij2cyfrowa(liczba):
    if liczba[1]==1:
        return nast[liczba[1]*10+liczba[0]]
    else:
        return dzies[int(liczba[1])]+" "+cyf[int(liczba[0])]

def nazwij3cyfrowa(liczba):    
    if len(liczba)==1:
        return cyf[liczba[0]]
    elif len(liczba)==2:
        return nazwij2cyfrowa(liczba)
    else:
        return sety[int(liczba[2])]+" "+nazwij2cyfrowa(liczba[:2])        
        
def nazwij(arg):
        nums={0:{1:"",
                 2:"",
                 5:""},
              1:{1:"tysiąc",
                 2:"tysiące",
                 5:"tysięcy"},
              2:{1:"milion",
                 2:"miliony",
                 5:"milionów"}}
        
        wynik=""
        lista=[]
        arg=arg[::-1]
        for s in arg:
            lista.append(int(s))

        if len(lista)==1 and lista[0]==0:
            print "zero"
            return
        
        ile1=len(lista)//3
        ile2=len(lista)%3
        
        for i in range(ile1):
            liczba=lista[(i*3+2)]*100+lista[(i*3+1)]*10+lista[(i*3)]
            if liczba!=0:   
                if liczba<10:
                    if liczba==1:
                        wynik=nums[i][1]+" "+wynik 
                    elif liczba<5:
                        wynik=nums[i][2]+" "+wynik
                    else:
                        wynik=nums[i][5]+" "+wynik                    
                    wynik=nazwij3cyfrowa(lista[(i*3):(i*3+1)])+" "+wynik
                elif liczba<100:
                    if lista[(i*3+1)]!=1 and 1<lista[(i*3)]<5:
                        wynik=nums[i][2]+" "+wynik
                    else:
                        wynik=nums[i][5]+" "+wynik                    
                    wynik=nazwij3cyfrowa(lista[(i*3):(i*3+2)])+" "+wynik
                else:
                    if lista[(i*3+1)]!=1 and 1<lista[(i*3)]<5:
                        wynik=nums[i][2]+" "+wynik
                    else:
                        wynik=nums[i][5]+" "+wynik                        
                    wynik=nazwij3cyfrowa(lista[(i*3):((i+1)*3)])+" "+wynik
                
        if ile2==1:
            if lista[ile1*3]==1:
                wynik=nums[ile1][1]+" "+wynik 
            elif lista[ile1*3]<5:
                wynik=nums[ile1][2]+" "+wynik
            else:
                wynik=nums[ile1][5]+" "+wynik 
            wynik=nazwij3cyfrowa(lista[(ile1*3):])+" "+wynik
        elif ile2==2:
            if lista[(ile1*3+1)]!=1 and 1<lista[(ile1*3)]<5:
                wynik=nums[ile1][2]+" "+wynik
            else:
                wynik=nums[ile1][5]+" "+wynik                    
            wynik=nazwij3cyfrowa(lista[(ile1*3):])+" "+wynik
        
        print wynik

if __name__=='__main__':
    for s in sys.argv[1:]:
        nazwij(s)
    #nazwij('321001125')
    #nazwij('152460')
    #nazwij('100259')
    #nazwij('100000024')
    #nazwij('34689502')
    #nazwij('0')

