#/usr/bin/env python
#-*- coding: utf-8 -*-

import sys,subprocess

def stworz_komende(tytul,xlab,ylab,kolumna,log):
	title='set title "'+tytul+'" \n'
	xlabel='set xlabel "'+xlab+'"\n'
	ylabel='set ylabel "'+ylab+'"\n'
	skale='set yrange [0:]\n'
	plot='plot "'+log+'" using '+str(kolumna)+':xticlabels(1) with boxes\n'
	return title+xlabel+ylabel+skale+plot

def rysuj(log):
	komendy=[stworz_komende("Liczba prob wejscia do sekcji","proces","ile prob",2,log), \
			stworz_komende("Liczba wejsc do sekcji","proces","ile wejsc",3,log), \
			stworz_komende("Liczba wyjsc z sekcji","proces","ile wyjsc",4,log), \
			stworz_komende("Laczny czas oczekiwania na wejscie","proces","czas",5,log), \
			stworz_komende("Laczny czas w sekcji","proces","czas",6,log), \
			stworz_komende("Sredni czas oczekiwania na wejscie","proces","czas",7,log), \
			stworz_komende("Sredni czas w sekcji","proces","czas",8,log), \
			stworz_komende("Laczny czas pracy watku","proces","czas",9,log)]
	for komenda in komendy:
		subprocess.Popen(['gnuplot','-persist'],stdin=subprocess.PIPE,stdout=subprocess.PIPE).communicate(komenda)

if __name__=='__main__':
	rysuj(sys.argv[1])
