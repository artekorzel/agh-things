program palindromy;
var
i:integer;
a,d,e:int64;
begin
 for i:=197 to 200 do begin
  a:=i;
  repeat
  d:=0;
  e:=a;
  while (e>0) do begin
   d:= d*10 + e mod 10;
   e:= e div 10
   end;
  if a<>d then a:=a+d;
  until(a=d);
  if a=d then writeln(i,'-',a)
 end;
 readln()
end.
