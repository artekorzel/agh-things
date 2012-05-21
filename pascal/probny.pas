const max=2;

var a,b:int64;
        i,j,k:integer;
        tab:array[0..9,0..9] of int64;
        r:array[0..max] of int64;
begin
        for i:=1 to 9 do for j:=0 to 9 do tab[i,j]:=trunc(exp(j*ln(i)));
        i:=0; for j:=0 to 9 do tab[i,j]:=0;

        b:=tab[5,4];
                k:=0;
                while b<>0 do begin
                        b:=b+r[k];
                        r[k]:=b mod 10;
                        b:=b div 10;
                        inc(k)
                end;

        b:=tab[2,4];
                k:=0;
                while b<>0 do begin
                        b:=b+r[k];
                        r[k]:=b mod 10;
                        b:=b div 10;
                        inc(k)
                end;
                k:=max;
        while r[k]=0 do dec(k);
for j:=k downto 0 do write(r[j]); writeln;

        readln
end.
