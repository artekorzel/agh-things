import sys, threading, datetime, time, Ice, MyCommunicator

to_notify = False

class NotifyThread(threading.Thread):
    def __init__(self, hello_callback):
        threading.Thread.__init__(self)
        self.hello_callback = hello_callback
        
    def run(self):
        try:
            while to_notify:
                self.hello_callback()
                time.sleep(10)
        except:
            print "Program finished"
            
class UserCallbackI(MyCommunicator.UserCallback):
    def sendNewMessage(self, msg, current=None):
        print "%s %s: %s" % (
                datetime.datetime.fromtimestamp(msg.time).isoformat(' '), 
                msg.userName, 
                msg.content)
        
class Client(Ice.Application):
    def __init__(self):
        self.user_name = None
        self.password = None
        
    def get_credentials(self):
        self.user_name = raw_input("User name: ")
        self.password = raw_input("Password: ")

    def register(self, chatManager):
        self.get_credentials()
        try:
            chatManager.register(self.user_name, self.password)
        except:
            print "Cannot register!"
        
    def log_in(self, chatManager):
        try:
            adapter = self.communicator().createObjectAdapter("")
            ident = Ice.Identity()
            ident.name = self.user_name
            base = adapter.add(UserCallbackI(), ident)
            user_callback_proxy = MyCommunicator.UserCallbackPrx.uncheckedCast(base)        
            adapter.activate()
            chatManager.ice_getConnection().setAdapter(adapter)
            
            self.session = self.room.logIn(self.user_name, self.password, user_callback_proxy)
            self.notify_thread = NotifyThread(chatManager.hello) 
            global to_notify
            to_notify = True   
            self.notify_thread.start()
        except:
            print "Unknown user!"

    def get_room_history(self):
        try:
            messages = self.room.getRoomHistory(self.session)
            for message in messages:
                print "%s %s: %s" % (
                        datetime.datetime.fromtimestamp(message.time).isoformat(' '), 
                        message.userName, 
                        message.content)
        except:            
            print "Unknown user!"

    def send_message(self):
        try:
            message_content = raw_input("Your message: ")
            self.room.sendMessage(self.session, MyCommunicator.Message(int(time.time()), self.user_name, message_content))
        except:
            print "Unknown user!"

    def log_out(self):
        try:
            self.room.logOut(self.session)
            global to_notify
            to_notify = False   
        except:
            print "Unknown user!"

    def obtain_room(self, chatManager):
        if not self.user_name:
            self.get_credentials()
        room_name = raw_input("Room name: ")
        endpoints = self.communicator().getProperties().getProperty("MyCommunicator.Proxy").split(":")[1]
        base = self.communicator().stringToProxy("Rooms/" + room_name + ":" + endpoints)
        self.room = MyCommunicator.RoomPrx.checkedCast(base)        
        while True:
            operation = raw_input("Choose operation:\n1: log in\n2: get room history\n3: send message\n4: log out\n[else]: quit\n")
            if operation == '1':
                self.log_in(chatManager)
            elif operation == '2':
                self.get_room_history()
            elif operation == '3':
                self.send_message()
            elif operation == '4':
                self.log_out()
            else:
                break
            
    def interruptCallback(self, sig):
        global to_notify
        to_notify = False 
        Ice.Application._shutdownOnInterruptCallback(self, sig)       
        
    def run(self, args):
        self.callbackOnInterrupt()        
        base = self.communicator().propertyToProxy("MyCommunicator.Proxy")
        chatManager = MyCommunicator.ChatManagerPrx.checkedCast(base)
        if not chatManager:
            raise RuntimeError("Invalid proxy")    
        while True:
            operation = raw_input("Choose operation:\n1: register\n2: obtain room\n[else]: quit\n")
            if operation == '1':
                self.register(chatManager)
            elif operation == '2':
                self.obtain_room(chatManager)
            else:
                return 0
                    
        
app = Client()
sys.exit(app.main(sys.argv))