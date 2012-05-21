program dwadopot;
var
t:array[1..305]of integer;
i,m:integer;
p:integer;
begin

t[1]:=1;
for m:=2 to 305 do t[m]:=0;
for i:=1 to 1000 do begin

m:=1;
p:=0;
repeat
   t[m]:=t[m]*2 + p;
   p:=t[m] div 10;
   t[m]:=t[m] mod 10;
   inc(m);
until m=305;
end;
for m:=305 downto 1 do write(t[m]);
readln();
end.
