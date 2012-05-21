const max=5;

type    indeksy=1..max;
        tab=array[indeksy] of integer;

procedure komb(var t:tab; m,n:integer);
var
        wynik:tab;
        uzyte: set of indeksy;
procedure kom(aktm,aktn:integer);
var k:integer;
begin
        if aktn=n+1 then begin
                for k:=1 to n do write(wynik[k], ' ');
                writeln
        end else
                for aktm:=1 to m do
                  if not (aktm in uzyte) then begin
                        uzyte:=uzyte+[aktm];
                        wynik[aktn]:=t[aktm];
                        kom(aktm+1,aktn+1);
                        uzyte:=uzyte-[aktm];
                  end
end;

begin
        uzyte:=[];
        kom(1,1)
end;
const t:tab=(1,2,3,4,5);

begin
        komb(t,5,3);
        readln
end.

