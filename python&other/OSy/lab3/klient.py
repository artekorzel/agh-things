import pickle
import pprint

with open("/home/artur/lab/plik","r") as p:
    dane=pickle.load(p)
pprint.pprint(dane)
