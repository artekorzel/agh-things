const max=5;

type tab=array[1..max] of integer;

procedure komb(var t:tab; m,n:integer);
var
        wynik:tab;
procedure kom(aktm,aktn:integer);
var k:integer;
begin
        if aktn=n+1 then begin
                for k:=1 to n do write(wynik[k], ' ');
                writeln
        end else
                for aktm:=1 to m do begin
                        wynik[aktn]:=t[aktm];
                        kom(aktm+1,aktn+1);
                end
end;

begin
        kom(1,1)
end;
const t:tab=(1,2,3,4,5);

begin
        komb(t,5,3);
        readln
end.

