module MiddlewareTestbed {
   interface Item;

   exception ItemNotExists {};

   exception ItemAlreadyExists {};

   exception ItemBusy {};

   interface AFactory {
      Item* create_item(string name, string type) throws ItemAlreadyExists;
      Item* take_item(string name) throws ItemNotExists, ItemBusy;
      void release_item(string name) throws ItemNotExists;
   };

   interface Item {
      idempotent string name();
      idempotent int get_item_age();
   };

   interface ItemA extends Item {
      void actionA(float a, out int b);
   };

   interface ItemB extends Item {
      float actionB(string a);
   };
   
   interface ItemC extends Item {
      void actionC(int a1, out int a2, out short b);
   };
};