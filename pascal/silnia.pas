program ppp;
const max=2600;
var
tmp,n,i,j,r:integer;
t:array[0..max]of integer;
begin
 for i:=1 to max do t[i]:=0;
 t[0]:=1;
 readln(n);
 for i:=1 to n do begin
  r:=0;
  for j:=0 to max do begin
   tmp:=t[j]*i +r;
   t[j]:=tmp mod 10;
   r:=tmp div 10
   end;
   end;
  for i:=max downto 0 do write(t[i]);
  readln();
end.