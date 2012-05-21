program armstronga;
var
j,l,m:int64;
i,k,n:integer;
begin

 for i:=1 to 32000 do begin
 j:=i;
 k:=0;
 while(j>0) do begin
  inc(k);
  j:=j div 10
  end;
 j:=i;
 l:=0;
 while(j>0) do begin
  m:=1;
  for n:=1 to k do  m:=m*(j mod 10);
  l:=l + m;
  j:=j div 10
  end;

 if l=i then writeln(i);
 end;
 readln();
end.