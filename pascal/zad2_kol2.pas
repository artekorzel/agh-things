const n=5;
type tab=array[1..n] of integer;

var t:tab;
i:integer;

function znajdz(var t:tab):integer;
var i,suma:integer;

        procedure ala(sumind,sumel,k:integer);
        var j,tmp:integer;
        begin
            if (suma=0) then
                if (k=i) then begin
                        if sumind=sumel then suma:=sumind
                end else for j:=1 to n do if t[j]<>0 then begin
                                tmp:=t[j];
                                t[j]:=0;
                                ala(sumind+j,sumel+tmp,k+1);
                                t[j]:=tmp
                end
        end;
begin
        suma:=0;
        i:=1;
        while (suma=0) and (i<=n) do begin
                ala(0,0,0);
                inc(i)
        end;
        znajdz:=suma
end;

begin
        for i:=1 to n do read(t[i]);
        writeln(znajdz(t));
        readln()
end.