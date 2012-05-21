type
        tablica2=array of array of real;

var
t:tablica2;
rozmiar,i,j:integer;
wyzn,x:real;

procedure wyznacznik(rozmiar:integer; var t:tablica2; var a:real);
var
t2:tablica2;
b,c:real;
i,j,k,l:integer;
begin

        if rozmiar=1 then a:=t[0,0]
        else if rozmiar=2 then a:=t[0,0]*t[1,1]-t[0,1]*t[1,0]
        else begin
                a:=0;
                j:=rozmiar-1;
                SetLength(t2,j,j);
                for i:=0 to j do begin
                    for k:=0 to j-1 do begin
                        for l:=0 to i-1 do t2[l,k]:=t[l,k];
                        for l:=i+1 to j do t2[l-1,k]:=t[l,k]
                    end;

                    wyznacznik(j,t2,b);
                    c:=b*t[i,j];
                    if (i+j) mod 2 = 1 then
                        c:=-c;
                    a:=a+c
                end
        end
end;

begin
        randomize;
        readln(rozmiar);
        SetLength(t,rozmiar,rozmiar);
        while not eoln do begin
                for i:=0 to rozmiar-1 do
                        for j:=0 to rozmiar-1 do begin
                                read(x);
                                t[i,j]:=x
                        end
        end;
        for i:=0 to rozmiar-1 do begin
                for j:=0 to rozmiar-1 do
                        write(t[i,j],' ');
                writeln();
        end;
        wyznacznik(rozmiar,t,wyzn);
        writeln(wyzn);
        readln(x)
end.




