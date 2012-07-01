import subprocess
import Polecenia

class PoleceniaPython(Polecenia):
    def __init__(self):
        pass
    def mail(self,adresat,opcja,tresc):
        subprocess.Popen(["mail", "-s", "Laby", opcja, adresat],
                         stdin=subprocess.PIPE).communicate(tresc)
        return tresc
    def cut(self,string,opcja):
        pass