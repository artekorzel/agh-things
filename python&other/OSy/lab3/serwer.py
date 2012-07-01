import pickle

def publicVar(k):
    def f(*args,**kwargs):
        obj=object.__new__(k)
        k.__init__(obj,*args)
        print obj       
        with open("/home/artur/lab/plik","w") as p:
            pickle.dump(obj.__dict__,p)
        return obj
    return f

@publicVar
class Klasa(object):
    def __init__(self,a,b,c):
        self.a=a
        self.b=b
        self.c=c
    def __call__(self):
        pass

instancja=Klasa(1,2,[1,2,4])

