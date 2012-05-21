program wypise;
var
m,e:array[0..100]of integer;
i,j,p,r:integer;
begin
m[0]:=1;
e[0]:=0;
 for j:=1 to 70 do begin
    p:=0;
    for i:=100 downto 0 do begin
    p:=e[i]+m[i]+p;
    e[i]:=p mod 10;
    p:= p div 10;
    end;

    r:=0;
    for i:=0 to 100 do begin
    r:=r*10+m[i];
    m[i]:=r div j;
    r:= r mod j;
    end;
 end;
    write(e[0],',');
    for i:=1 to 100 do write(e[i]);

 readln();
end.
