#!/usr/bin/python
# -*- coding: utf-8 -*-
    
class Komponent(object):
    def __init__(self,_nazwa,_cena):
        self.nazwa=_nazwa
        self.cena=_cena
    def wypisz(self,k=0):
        print ' '*3*k,'Komponent:',self.nazwa
    def akceptuj(self,odwiedzajacy):
        pass
        
class Kompozyt(Komponent):
    def __init__(self,_nazwa):
        Komponent.__init__(self,_nazwa,0)
        self.lista=[]
    def dodaj(self,komponent):
        self.lista.append(komponent)
    def wypisz(self,k=0):
        print ' '*3*k,'Kompozyt:',self.nazwa+':'
        for i in self.lista:
            i.wypisz(k+1)
    def akceptuj(self,odwiedzajacy):
        for i in self.lista:
            i.akceptuj(odwiedzajacy)

class Samochod(Komponent):
    def __init__(self,_nazwa,_cena):
        Komponent.__init__(self,_nazwa,_cena)
    def akceptuj(self,odwiedzajacy):
        odwiedzajacy.odwiedzSamochod(self)
        
class Silnik(Komponent):
    def __init__(self,_nazwa,_cena):
        Komponent.__init__(self,_nazwa,_cena)
    def akceptuj(self,odwiedzajacy):
        odwiedzajacy.odwiedzSilnik(self)

class Cylinder(Komponent):
    def __init__(self,_nazwa,_cena):
        Komponent.__init__(self,_nazwa,_cena)
    def akceptuj(self,odwiedzajacy):
        odwiedzajacy.odwiedzCylinder(self)

class Tlok(Komponent):
    def __init__(self,_nazwa,_cena):
        Komponent.__init__(self,_nazwa,_cena)
    def akceptuj(self,odwiedzajacy):
        odwiedzajacy.odwiedzTlok(self)

class Rozrzad(Komponent):
    def __init__(self,_nazwa,_cena):
        Komponent.__init__(self,_nazwa,_cena)
    def akceptuj(self,odwiedzajacy):
        odwiedzajacy.odwiedzRozrzad(self)

class Podwozie(Komponent):
    def __init__(self,_nazwa,_cena):
        Komponent.__init__(self,_nazwa,_cena)
    def akceptuj(self,odwiedzajacy):
        odwiedzajacy.odwiedzPodwozie(self)
        
class Hamulce(Komponent):
    def __init__(self,_nazwa,_cena):
        Komponent.__init__(self,_nazwa,_cena)
    def akceptuj(self,odwiedzajacy):
        odwiedzajacy.odwiedzHamulce(self)
        
class Zawieszenie(Komponent):
    def __init__(self,_nazwa,_cena):
        Komponent.__init__(self,_nazwa,_cena)
    def akceptuj(self,odwiedzajacy):
        odwiedzajacy.odwiedzZawieszenie(self)

class Nadwozie(Komponent):
    def __init__(self,_nazwa,_cena):
        Komponent.__init__(self,_nazwa,_cena)
    def akceptuj(self,odwiedzajacy):
        odwiedzajacy.odwiedzNadwozie(self)
        
class Drzwi(Komponent):
    def __init__(self,_nazwa,_cena):
        Komponent.__init__(self,_nazwa,_cena)
    def akceptuj(self,odwiedzajacy):
        odwiedzajacy.odwiedzDrzwi(self)
        
class Zderzak(Komponent):
    def __init__(self,_nazwa,_cena):
        Komponent.__init__(self,_nazwa,_cena)
    def akceptuj(self,odwiedzajacy):
        odwiedzajacy.odwiedzZderzak(self)

class Wnetrze(Komponent):
    def __init__(self,_nazwa,_cena):
        Komponent.__init__(self,_nazwa,_cena)
    def akceptuj(self,odwiedzajacy):
        odwiedzajacy.odwiedzWnetrze(self)
        
class Fotel(Komponent):
    def __init__(self,_nazwa,_cena):
        Komponent.__init__(self,_nazwa,_cena)
    def akceptuj(self,odwiedzajacy):
        odwiedzajacy.odwiedzFotel(self)
        
class Kierownica(Komponent):
    def __init__(self,_nazwa,_cena):
        Komponent.__init__(self,_nazwa,_cena)
    def akceptuj(self,odwiedzajacy):
        odwiedzajacy.odwiedzKierownica(self)
        
class PlynHamulcowy(Komponent):
    def __init__(self,_nazwa,_cena):
        Komponent.__init__(self,_nazwa,_cena)
    def akceptuj(self,odwiedzajacy):
        odwiedzajacy.odwiedzPlynHamulcowy(self)

class Koszyk(object):
    def __init__(self):
        self.komponenty=[]
    def dodaj(self,komponent):
        self.komponenty.append(komponent)
    def akceptuj(self,odwiedzajacy):
        for i in self.komponenty:
            i.akceptuj(odwiedzajacy)
        
class Odwiedzajacy(object):
    def __init__(self):
        pass
    def odwiedzSamochod(self,samochod):
        pass
    def odwiedzSilnik(self,silnik):
        pass
    def odwiedzCylinder(self,cylinder):
        pass
    def odwiedzTlok(self,tlok):
        pass
    def odwiedzRozrzad(self,rozrzad):
        pass
    def odwiedzPodwozie(self,podwozie):
        pass
    def odwiedzHamulce(self,hamulce):
        pass
    def odwiedzZawieszenie(self,zawieszenie):
        pass
    def odwiedzNadwozie(self,nadwozie):
        pass
    def odwiedzDrzwi(self,drzwi):
        pass
    def odwiedzZderzak(self,zderzak):
        pass
    def odwiedzWnetrze(self,wnetrze):
        pass
    def odwiedzFotel(self,fotel):
        pass
    def odwiedzKierownica(self,kierownica):
        pass
    def odwiedzPlynHamulcowy(self,plyn):
        pass
    def wypisz(self):
        pass
        
class OdwiedzajacyCena(Odwiedzajacy):
    def __init__(self):
        self.cena=0.0
    def odwiedzSamochod(self,samochod):
        self.cena+=samochod.cena
    def odwiedzSilnik(self,silnik):
        self.cena+=silnik.cena
    def odwiedzCylinder(self,cylinder):
        self.cena+=cylinder.cena
    def odwiedzTlok(self,tlok):
        self.cena+=tlok.cena
    def odwiedzRozrzad(self,rozrzad):
        self.cena+=rozrzad.cena
    def odwiedzPodwozie(self,podwozie):
        self.cena+=podwozie.cena
    def odwiedzHamulce(self,hamulce):
        self.cena+=hamulce.cena
    def odwiedzZawieszenie(self,zawieszenie):
        self.cena+=zawieszenie.cena
    def odwiedzNadwozie(self,nadwozie):
        self.cena+=nadwozie.cena
    def odwiedzDrzwi(self,drzwi):
        self.cena+=drzwi.cena
    def odwiedzZderzak(self,zderzak):
        self.cena+=zderzak.cena
    def odwiedzWnetrze(self,wnetrze):
        self.cena+=wnetrze.cena
    def odwiedzFotel(self,fotel):
        self.cena+=fotel.cena
    def odwiedzKierownica(self,kierownica):
        self.cena+=kierownica.cena
    def odwiedzPlynHamulcowy(self,plyn):
        self.cena+=plyn.cena
    def wypisz(self):
        print "Cena łączna produktów wynosi:",str(self.cena)
        
class OdwiedzajacyProducent(Odwiedzajacy):
    def __init__(self,prod):
        self.ile=0
        self.cena=0.0
        self.producent=prod
    def odwiedzSamochod(self,samochod):
        if samochod.nazwa==self.producent:
            self.ile+=1
            self.cena+=samochod.cena
    def odwiedzSilnik(self,silnik):
        if silnik.nazwa==self.producent:
            self.ile+=1
            self.cena+=silnik.cena
    def odwiedzCylinder(self,cylinder):
        if cylinder.nazwa==self.producent:
            self.ile+=1
            self.cena+=cylinder.cena
    def odwiedzTlok(self,tlok):
        if tlok.nazwa==self.producent:
            self.ile+=1
            self.cena+=tlok.cena
    def odwiedzRozrzad(self,rozrzad):
        if rozrzad.nazwa==self.producent:
            self.ile+=1
            self.cena+=rozrzad.cena
    def odwiedzPodwozie(self,podwozie):
        if podwozie.nazwa==self.producent:
            self.ile+=1
            self.cena+=podwozie.cena
    def odwiedzHamulce(self,hamulce):
        if hamulce.nazwa==self.producent:
            self.ile+=1
            self.cena+=hamulce.cena
    def odwiedzZawieszenie(self,zawieszenie):
        if zawieszenie.nazwa==self.producent:
            self.ile+=1
            self.cena+=zawieszenie.cena
    def odwiedzNadwozie(self,nadwozie):
        if nadwozie.nazwa==self.producent:
            self.ile+=1
            self.cena+=nadwozie.cena
    def odwiedzDrzwi(self,drzwi):
        if drzwi.nazwa==self.producent:
            self.ile+=1
            self.cena+=drzwi.cena
    def odwiedzZderzak(self,zderzak):
        if zderzak.nazwa==self.producent:
            self.ile+=1
            self.cena+=zderzak.cena
    def odwiedzWnetrze(self,wnetrze):
        if wnetrze.nazwa==self.producent:
            self.ile+=1
            self.cena+=wnetrze.cena
    def odwiedzFotel(self,fotel):
        if fotel.nazwa==self.producent:
            self.ile+=1
            self.cena+=fotel.cena
    def odwiedzKierownica(self,kierownica):
        if kierownica.nazwa==self.producent:
            self.ile+=1
            self.cena+=kierownica.cena
    def odwiedzPlynHamulcowy(self,plyn):
        if plyn.nazwa==self.producent:
            self.ile+=1
            self.cena+=plyn.cena
    def wypisz(self):
        print "Producent:",self.producent,"\n\tLiczba produktów danego producenta:",str(self.ile),"\n\tCena łączna produktów:",str(self.cena)

class OdwiedzajacyKategoria(Odwiedzajacy):
    def __init__(self,kat):
        self.cena=0.0
        self.kategoria=type(kat)
    def odwiedzSamochod(self,samochod):
        if isinstance(samochod,self.kategoria):
            self.cena+=samochod.cena
    def odwiedzSilnik(self,silnik):
        if isinstance(silnik,self.kategoria):
            self.cena+=silnik.cena
    def odwiedzCylinder(self,cylinder):
        if isinstance(cylinder,self.kategoria):
            self.cena+=cylinder.cena
    def odwiedzTlok(self,tlok):
        if isinstance(tlok,self.kategoria):
            self.cena+=tlok.cena
    def odwiedzRozrzad(self,rozrzad):
        if isinstance(rozrzad,self.kategoria):
            self.cena+=rozrzad.cena
    def odwiedzPodwozie(self,podwozie):
        if isinstance(podwozie,self.kategoria):
            self.cena+=podwozie.cena
    def odwiedzHamulce(self,hamulce):
        if isinstance(hamulce,self.kategoria):
            self.cena+=hamulce.cena
    def odwiedzZawieszenie(self,zawieszenie):
        if isinstance(zawieszenie,self.kategoria):
            self.cena+=zawieszenie.cena
    def odwiedzNadwozie(self,nadwozie):
        if isinstance(nadwozie,self.kategoria):
            self.cena+=nadwozie.cena
    def odwiedzDrzwi(self,drzwi):
        if isinstance(drzwi,self.kategoria):
            self.cena+=drzwi.cena
    def odwiedzZderzak(self,zderzak):
        if isinstance(zderzak,self.kategoria):
            self.cena+=zderzak.cena
    def odwiedzWnetrze(self,wnetrze):
        if isinstance(wnetrze,self.kategoria):
            self.cena+=wnetrze.cena
    def odwiedzFotel(self,fotel):
        if isinstance(fotel,self.kategoria):
            self.cena+=fotel.cena
    def odwiedzKierownica(self,kierownica):
        if isinstance(kierownica,self.kategoria):
            self.cena+=kierownica.cena
    def odwiedzPlynHamulcowy(self,plyn):
        if isinstance(plyn,self.kategoria):
            self.cena+=plyn.cena
    def wypisz(self):
        print "Cena łączna produktów z kategorii",self.kategoria.__name__,"wynosi:",str(self.cena)

if __name__=='__main__':    
    silnik=Silnik('Honda',5000.00) 
    tlok=Tlok('Fiat',100.99)
    cylinder=Cylinder('Ford',200.59)
    samochod=Samochod('Ford',95000.00)
    samochod2=Samochod('Nissan',255000.00)
    koszyk=Koszyk()
    koszyk.dodaj(silnik)
    koszyk.dodaj(tlok)
    koszyk.dodaj(cylinder)
    koszyk.dodaj(samochod)
    koszyk.dodaj(samochod2)
    cena=OdwiedzajacyCena() 
    koszyk.akceptuj(cena)
    cena.wypisz()
    producent=OdwiedzajacyProducent('Honda')
    koszyk.akceptuj(producent)
    producent.wypisz()
    kategoria1=OdwiedzajacyKategoria(silnik) 
    kategoria2=OdwiedzajacyKategoria(samochod) 
    koszyk.akceptuj(kategoria1) 
    kategoria1.wypisz()
    koszyk.akceptuj(kategoria2)
    kategoria2.wypisz()
    
    silnik.wypisz()
    
    silnik2=Kompozyt('Ford') 
    silnik2.dodaj(tlok) 
    silnik2.dodaj(cylinder) 
    podwozie=Kompozyt('Ferrari')
    hamulce=Hamulce('Brembo',10000.00)  
    podwozie.dodaj(hamulce)
    samochod3=Kompozyt('Opel') 
    samochod3.dodaj(podwozie) 
    samochod3.dodaj(silnik2) 
    samochod3.wypisz()
        
