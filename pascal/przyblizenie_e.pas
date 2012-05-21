program dw;
var
e,m:real;
i,j:integer;
begin
e:=1.0;
m:=1.0;
for j:=1 to 70 do begin
m:=m/j;
e:=e+m;
end;
write(e);
read(j);
end.