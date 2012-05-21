const max=20;
var
tab:array[0..9,0..9] of int64;
t,r:array[0..max] of integer;
i,j,k,a:integer;
b:int64;
bool:boolean;

begin
        for i:=1 to 9 do for j:=0 to 9 do tab[i,j]:=trunc(exp(j*ln(i)));
        i:=0; for j:=0 to 9 do tab[i,j]:=0;

        for i:=0 to max do t[i]:=0;

        t[1]:=1;
        repeat

        for i:=0 to max do r[i]:=0;

        a:=1;
        i:=0;
        while a<>0 do begin
                a:=t[i]+a;
                t[i]:=a mod 10;
                a:=a div 10;
                inc(i)
        end;

        i:=max;
        while t[i]=0 do dec(i);
{for j:=i downto 0 do write(t[j]); writeln; }
        for j:=i downto 1 do begin
                b:=tab[t[j],t[j-1]];
                k:=0;
                while b<>0 do begin
                        b:=b+r[k];
                        r[k]:=b mod 10;
                        b:=b div 10;
                        inc(k)
                end;
                if k>i+1 then break
        end;

        b:=tab[t[0],t[i]];
        k:=0;
        while b<>0 do begin
                b:=b+r[k];
                r[k]:=b mod 10;
                b:=b div 10;
                inc(k)
        end;

        k:=max;
        while r[k]=0 do dec(k);
{for j:=k downto 0 do write(r[j]); writeln;}
        if i=k then begin
                bool:=true;
                for j:=i downto 0 do if t[j]<>r[j] then bool:=false;
                if bool then begin
                        for j:=i downto 0 do write(t[j]);
                        writeln
                end
        end
        until t[max]=1;
end.



