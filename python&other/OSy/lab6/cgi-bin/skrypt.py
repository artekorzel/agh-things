#!/usr/bin/env python
#-*-coding: utf-8 -*-
#Uruchomic serwer WWW komenda 'python -m CGIHTTPServer 8000 .' 
#Utworzyc katalog 'cgi-bin' i umiescic  w nim ponizszy skrypt Python
#Wykonac chmod 755 skrypt.py
#Jezeli skrypt ma generowac dokument HTML nalezy w linii 8 zastapic slowo "plain" slowem "html"

import os,sys,re
print "Content-Type: text/html"
print
metoda=os.environ['REQUEST_METHOD']
if metoda == "GET":
  dane=os.environ['QUERY_STRING'] 
else:
  dlugosc=int(os.environ['CONTENT_LENGTH'])
  dane=sys.stdin.read(dlugosc)
  print "Przegladarka zakodowala dane przy uzyciu metody: '"+os.environ['CONTENT_TYPE']+"'"
  print '*' * 60
  print '\n' * 3
#print dane #Wypisuje zakodowane dane

dane2=re.sub('\+',' ',dane)
lista=re.split('&',dane2)
print "<table>"
for l in lista:
	print "<tr>"
	pole=re.split('=',l)
	for p in pole:
		print "<th>"+p+"</th>"
	print "</tr>"
print "</table>"
