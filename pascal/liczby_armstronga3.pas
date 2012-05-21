program armstronga;
const max=100;
var
t,p,r:array[1..max] of integer;
s:array[1..max,1..max]of integer;
b:Boolean;
i,j,k,l:integer;
a,c,e:int64;

begin
   for i:=2 to max do t[i]:=0;
   t[1]:=1;

   repeat

   j:=max;
   while (t[j]=0) do dec(j);
   for i:=1 to max do p[i]:=0;

   for i:=1 to j do r[i]:=t[i];


   i:=1;

   for k:=1 to j do begin

    c:=0;
    while(i<j) do begin
     for l:=1 to j+1 do begin
      r[l]:=r[l]*t[k] + c;
      c:= r[l] div 10;
      r[l]:= r[l] mod 10;
     end;
    end;
    e:=0;
    for l:=1 to j+2 do begin
     p[l]:=p[l]+r[l]+e;
     e:= p[l] div 10;
     p[l]:=p[l] mod 10;
     end;
   end;


   b:=true;
   for i:=1 to j do begin if t[i]<>p[i] then b:=false; end;
   if b then begin for i:=j downto 1 do write(t[i]); end;
   if b then writeln();

   c:=1;
   for i:=1 to j+1 do begin
    t[i]:=t[i] + c;
    c:=t[i] div 10;
    t[i]:= t[i] mod 10;
    end;

   until(t[61]=9);
end.
