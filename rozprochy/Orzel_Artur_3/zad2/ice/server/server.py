import sys, MiddlewareTestbed, Ice, datetime, threading

class ItemI(MiddlewareTestbed.Item):
    def __init__(self, name):
        self.__name = name
        self.__creationDate = datetime.datetime.today()
        
    def name(self, current=None):    
        return self.__name
    
    def get_item_age(self, current=None):
        return (datetime.datetime.today() - self.__creationDate).total_seconds()


class ItemAI(MiddlewareTestbed.ItemA,ItemI):
    def __init__(self, name):
        ItemI.__init__(self, name)
        
    def actionA(self, a, current=None):
        return int(round(a))


class ItemBI(MiddlewareTestbed.ItemB,ItemI):
    def __init__(self, name):
        ItemI.__init__(self, name)
        
    def actionB(self, a, current=None):
        try:
            return float(a)
        except ValueError:
            return float("-inf")


class ItemCI(MiddlewareTestbed.ItemC,ItemI):
    def __init__(self, name):
        ItemI.__init__(self, name)
        
    def actionC(self, a1, current=None):
        return (a1 + 1, a1 % 32768)   


class AFactoryI(MiddlewareTestbed.AFactory):
    def __init__(self, adapter):
        self.__items = {}
        self.__itemsReserved = {}
        self.__adapter = adapter
        self.__mutex = threading.Lock()
        
    def create_item(self, name, type, current=None):
        self.__mutex.acquire()
        if name in self.__items:
            self.__mutex.release()
            raise MiddlewareTestbed.ItemAlreadyExists()
        
        if type == "A":
            proxy = self.__adapter.addWithUUID(ItemAI(name))
        elif type =="B":
            proxy = self.__adapter.addWithUUID(ItemBI(name))
        elif type =="C":
            proxy = self.__adapter.addWithUUID(ItemCI(name))
        else:
            self.__mutex.release()
            raise MiddlewareTestbed.ItemAlreadyExists("Type not found")
        
        nodeProxy = MiddlewareTestbed.ItemPrx.uncheckedCast(proxy)
        self.__items[name] = nodeProxy
        self.__itemsReserved[name] = True
        self.__mutex.release()
        return nodeProxy

    def take_item(self, name, current=None):
        self.__mutex.acquire()
        if name not in self.__items:
            self.__mutex.release()
            raise MiddlewareTestbed.ItemNotExists()
        
        if self.__itemsReserved[name]:
            self.__mutex.release()
            raise MiddlewareTestbed.ItemBusy()
        
        self.__itemsReserved[name] = True
        result = self.__items[name]
        
        self.__mutex.release()
        return result

    def release_item(self, name, current=None):
        self.__mutex.acquire()
        if name not in self.__items:
            self.__mutex.release()
            raise MiddlewareTestbed.ItemNotExists()
        
        self.__itemsReserved[name] = False
        self.__mutex.release()


class Server(Ice.Application):
    def run(self, args):
        self.shutdownOnInterrupt()
        adapter = self.communicator().createObjectAdapter("Factory")
        servant = AFactoryI(adapter)
        adapter.add(servant, self.communicator().stringToIdentity("Factory"))
        adapter.activate()
        self.communicator().waitForShutdown()
        if self.interrupted():
            print self.appName() + ": shutdown..."

        return 0
        
        
app = Server()
sys.exit(app.main(sys.argv))
