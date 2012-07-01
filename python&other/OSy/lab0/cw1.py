# -*- coding: utf-8 -*-
# łańcuchy wielolinijkowe - potrójny cudzysłów lub apostrof
lancuch1 = """moj pierwszy tekst
wielolinijkowy
"""
lancuch2 = "moj drugi tekst \nwielolinijkowy\n"
lancuch3 = '''moj trzeci tekst
wielolinijkowy
'''

print lancuch1
print lancuch2
print lancuch3

#wypis trzykrotny konkatenacji
print (lancuch1+lancuch2)*3

#napis w utf-8
lancuch = u'mój pierwszy łańcuch znaków w kodowaniu utf-8'

#wariacje na temat wypisywania fragmentow lancucha
print lancuch
print lancuch[0]
print lancuch[:2]
print lancuch[2:]
print lancuch[-2:-1]
print lancuch[-3:]
print lancuch[::2]

#sprawdzenie ze nie da sie modyfikowac napisu - bo jest immutable
#lancuch1[1] = 'o'

#lista z liczbami calkowitymi, liczba elementow, ilosc wystapien konkretnej
lista = [0,12,5,17,13,14,6,9,15,4,16,8,13,12,13]
print len(lista)
print lista.count(13)

#czy lista moze zawierac dane roznych typow - tak
lista2 = [15, 2, 'o', 'napis', 2]
print lista2

#slownik z kluczami jako literami i liczbami jako wartosciami
#liczba elementow, ilosc wystapien konkretnej
slownik = {'a':1, 'd':2, 'c':14, 'b':14, 'g':2}
print len(slownik)
print slownik.values().count(2)

#sprawdzenie czy wartosciami moga byc elementy roznych typow - tak
slownik2 = {'a':1, 'd':'jakis tekst'}
print slownik2




