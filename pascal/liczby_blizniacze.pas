program liczbyblizniacze;
var
a,b,d,e,g:integer;
c,f:int64;
begin
read(g);
 a:=3;
while(a<g)do
begin
  b:=1;
  c:=0;

  while(b*b<=a)do
  begin
   if a mod b = 0 then c:=c+b;
   b:=b+1;
  end;

 if c=1 then
 begin
  d:=a+2;
  e:=1;
  f:=0;

  while(e*e<=d)do
  begin
   if d mod e = 0 then f:=f+e;
   e:=e+1;
  end;

  if f=1 then writeln(a,' i ',d);
 end;
a:=a+2;
end;
read(g);
end.
