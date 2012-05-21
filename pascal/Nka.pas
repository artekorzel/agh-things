const   liczba=10;
        max=7;
        n=3;
type tab=array[1..max] of integer;

var
i:integer;
t:tab;
function enka(var t:tab; n,suma:integer):integer;
var
licznik:integer;
        procedure ala(k,aktsum,i:integer; var licznik:integer);

        begin
                if k>0 then begin
                        if aktsum<suma then
                                for i:=i to max-k+1 do
                                        ala(k-1,aktsum+t[i],i+1,licznik)
                end else if aktsum=suma then inc(licznik)
        end;

begin
        licznik:=0;
        ala(n,0,1,licznik);
        enka:=licznik
end;




begin
        for i:=1 to max do t[i]:=i;
        write(enka(t,n,liczba));
        readln
end.
