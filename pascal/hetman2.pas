const rozm=8;
      przek=rozm*2-1;

type tab1=array[1..rozm] of integer;
     tab2=array[1..przek] of boolean;

var
t:tab1;
prawe,lewe:tab2;
licznik,i:integer;

procedure wypisz(var t:tab1);
var i,j:integer;
begin
        writeln('rozw nr: ',licznik);
        for j:=1 to rozm do begin
                for i:=1 to t[j]-1 do write('0':3);
                write('1':3);
                for i:=t[j]+1 to rozm do write('0':3);
                writeln
        end
end;

procedure stawiaj(kolumna:integer);
var wiersz:integer;
begin
        if kolumna>rozm then begin
                inc(licznik);
                wypisz(t)
        end else for wiersz:=1 to rozm do
                if (t[wiersz]=0)
                   and (not prawe[kolumna+wiersz-1])
                     and (not lewe[rozm-wiersz+kolumna]) then begin
                        t[wiersz]:=kolumna;
                        prawe[kolumna+wiersz-1]:=true;
                        lewe[rozm-wiersz+kolumna]:=true;
                        stawiaj(kolumna+1);
                        t[wiersz]:=0;
                        prawe[kolumna+wiersz-1]:=false;
                        lewe[rozm-wiersz+kolumna]:=false
                end
end;

begin
	for i:=1 to rozm do t[i]:=0;
        for i:=1 to przek do begin
                prawe[i]:=false;
                lewe[i]:=false
        end;
        stawiaj(1);
        readln(i)
end.
