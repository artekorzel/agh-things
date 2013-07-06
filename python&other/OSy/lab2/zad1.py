import threading
import random

class Proces(object):
    def __init__(self,hn,r):
        self.hostname=hn
        self.rank=r
    def Get_rank(self):
        return self.rank
    def Get_hostname(self):
        return self.hostname

class Host(object):
    def __init__(self,name,numery):
        self.nazwa=name
        self.procesy=[]
        for i in numery:
            self.procesy.append(Proces(self.nazwa,i))
    def Get_proces(self,klucz):
        pr=Proces('',-1)
        for i in self.procesy:
            if i.Get_rank()==klucz:
                pr=i
        if pr.rank==-1:
            return None
        else:
            return pr

class Komunikator(object):
    def __init__(self,slownik):
        self.hosty={}
        self.rozmiar=0
        for i in slownik.keys():
            self.hosty[i]=Host(i,range(self.rozmiar,self.rozmiar+slownik[i]))
            self.rozmiar+=slownik[i]
    def Get_size(self):
        return self.rozmiar
    def __len__(self):
        return self.Get_size()
    def __getitem__(self,klucz):
        numer=0
        while klucz-len(self.hosty[self.hosty.keys()[numer]].procesy)>=0:
            klucz-=len(self.hosty[self.hosty.keys()[numer]].procesy)
            numer+=1
        return self.hosty.keys()[numer]
    def __iter__(self):
        self.uzyte=[]
        return self
    def next(self):
        if len(self.uzyte)==len(self):
            raise StopIteration
        i=random.randint(0,self.rozmiar-1)
        while i in self.uzyte:
            i=random.randint(0,self.rozmiar-1)
        self.uzyte.append(i)
        return self.hosty[self[i]].Get_proces(i)

if __name__=='__main__':
    hosty={'host1':2, 'host2':3, 'host3':6}
    k=Komunikator(hosty)
    print k.Get_size()
    print len(k)
    print k[9]
    for proces in k:
        print str(proces.Get_rank())+', '+proces.Get_hostname()
            
            
