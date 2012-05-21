const n=70;
var licznik:integer;

procedure ala(var licznik:integer; typ,suma:integer);

begin
        if suma<=n then begin
                if suma<>1 then inc(licznik);
                if typ=2 then ala(licznik,2,suma*2);
                if (typ in [2,3]) then ala(licznik,3,suma*3);
                ala(licznik,5,suma*5)
        end
end;

begin
        licznik:=0;
        ala(licznik,2,1);
        write(licznik);
        readln
end.