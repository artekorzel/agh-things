program dzielniki;
var
a,c,e:int64;

begin
 read(a);
 c:=1;
 e:=0;

 while(c*c<a)do
 begin

  if a mod c = 0 then
  begin

   if c<>1 then
   begin
    write(c,' ',a div c,' ');
    e:=e+c+(a div c);
   end

   else
   begin
    write(c,' ');
    e:=e+c;
   end;

  end;

  inc(c);
 end;

 if a=c*c then
 begin
  write(c,' ');
  e:=e+c;
 end;

 write(',',e);
 read(e)

end.
