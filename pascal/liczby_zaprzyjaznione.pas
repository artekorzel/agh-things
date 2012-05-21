program liczbyzaprzyjaznione;
var
a,b,g:integer;
d,c,e,f:int64;
begin
read(g);
a:=2;
while(a<g) do
begin
 b:=1;
 c:=0;
 while(b*b<a)do
 begin
  if a mod b = 0 then
  begin
   if b<>1 then begin c:=c+b+(a div b); end
   else c:=c+b;
  end;
 inc(b);
 end;

 if a=b*b then c:=c+b;

 d:=c;
 e:=1;
 f:=0;

  while(e*e<d)do
  begin
   if d mod e = 0 then
   begin
    if e<>1 then begin f:=f+e+(d div e); end
    else f:=f+e;
   end;
   inc(e);
  end;

 if d=e*e then f:=f+e;

 if a<>d then if f=a then writeln(a,' i ',d);
 a:=a+1;
end;
read(g);
end.
