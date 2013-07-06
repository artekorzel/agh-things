import sys, Ice, MyBank, Common
        
class Client(Ice.Application):
    def __init__(self):
        self.person_id = None
        self.password = None
    
    def get_credentials(self):
        self.person_id = raw_input("Person ID: ")
        self.password = raw_input("Password: ")   
        
    def log_in(self, chatManager):
        try:            
            self.session = self.account.logIn(self.person_id, self.password)
        except:
            print "Unknown user!"

    def get_balance(self):
        try:
            balance = self.account.getBalance(self.session)
            print "Current balance:", balance
        except:            
            print "Unknown user!"

    def withdraw_from_account(self):
        try:
            amount = raw_input("Amount to withdraw: ")
            self.account.withdrawFromAccount(self.session, float(amount))
        except Common.UnknownCredentials:
            print "Unknown user!"
        except:
            print "Incorrect amount!"

    def put_on_account(self):
        try:
            amount = raw_input("Amount to put: ")
            self.account.putOnAccount(self.session, float(amount))
        except Common.UnknownCredentials:
            print "Unknown user!"
        except:
            print "Incorrect amount!"

    def log_out(self):
        try:
            self.account.logOut(self.session)
        except:
            print "Unknown user!"

    def manage_account(self, accountManager):
        if not self.person_id:
            self.get_credentials()
        endpoints = self.communicator().getProperties().getProperty("MyBankOne.Proxy").split(":")[1]
#        endpoints = self.communicator().getProperties().getProperty("MyBankMulti.Proxy").split(":")[1]
        base = self.communicator().stringToProxy("Accounts/" + self.person_id + ":" + endpoints)
        self.account = MyBank.AccountPrx.checkedCast(base)        
        while True:
            operation = raw_input("Choose operation:\n1: logIn\n2: getBalance\n3: withdrawFromAccount\n4: putOnAccount\n5: logOut\n[else]: quit\n")
            if operation == '1':
                self.log_in(accountManager)
            elif operation == '2':
                self.get_balance()
            elif operation == '3':
                self.withdraw_from_account()
            elif operation == '4':
                self.put_on_account()
            elif operation == '5':
                self.log_out()
            else:
                break   
        
    def register(self, accountManager):
        self.get_credentials()
        try:
            accountManager.register(self.person_id, self.password)
        except:
            print "Account already exists!"
            
    def run(self, args):
        self.shutdownOnInterrupt()        
        base = self.communicator().propertyToProxy("MyBankOne.Proxy")
#        base = self.communicator().propertyToProxy("MyBankMulti.Proxy")
        accountManager = MyBank.AccountsManagerPrx.checkedCast(base)
        if not accountManager:
            raise RuntimeError("Invalid proxy")
        while True:
            operation = raw_input("Choose operation:\n1: register\n2: manage account\n[else]: quit\n")
            if operation == '1':
                self.register(accountManager)
            elif operation == '2':
                self.manage_account(accountManager)
            else:
                break;
        return 0
        
        
app = Client()
sys.exit(app.main(sys.argv))