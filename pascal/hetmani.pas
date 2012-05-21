{ Problem ustawiania hetman�w na szachownicy }
const
size = 8; { rozmiar szachownicy }
size2 = 15; { liczba przek�tnych size2 = 2*size-1 }
var
i,licznik : integer;
t : array [1..size] of integer; { tablica zawieraj�ca rozwi�zanie }
prawa,lewa : array [1..size2] of boolean; { przek�tne prawe i lewe }

procedure wypisz; { wypisz rozwi�zanie zawarte w tablicy t }
var
i,j : integer;
begin
        writeln('k = ',licznik);
        for j:=1 to size do begin
                for i:=1 to t[j]-1 do write(' .');
                write(' $');
                for i:=t[j]+1 to size do write(' .');
                writeln;
        end;
        writeln;
end;

procedure ustaw( kol : integer ); { ustaw hetmana w kolumnie kol }
var
wrs : integer;
begin
        if kol>size then begin
                wypisz; { je�eli ustawione wszystkie wypisz rozwi�zanie }
                inc(licznik)
        end else
        for wrs:=1 to size do { probuj ustawi� w wierszu wrs }
        if (t[wrs]=0) and { czy wolny wiersz }
                not prawa[wrs+kol-1] and { czy wolna prawa przek�tna }
                        not lewa[size-kol+wrs] { czy wolna lewa przek�tna }
        then begin
        { ustaw hetmana w kolumnie kol i wierszu wrs }
                t[wrs]:=kol;
                prawa[wrs+kol-1]:=true;
                lewa[size-kol+wrs]:=true;
        { przejdz do ustawiania hetmana w nast�pnej kolumnie }
                ustaw(kol+1);
        { wycofaj ustawienie hetmana w kolumnie kol i wierszu wrs }
                t[wrs]:=0;
                prawa[wrs+kol-1]:=false;
                lewa[size-kol+wrs]:=false;
        end
end;

begin
        licznik:=0;
        for i:=1 to size do t[i]:=0;
        for i:=1 to size2 do begin prawa[i]:=false; lewa[i]:=false end;
        ustaw(1); { ustaw pierwszego hetmana }
        readln(i)
end.
