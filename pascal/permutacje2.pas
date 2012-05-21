const n=3;
type tab=array[1..n] of integer;
     indeksy = 1..n;
var i:integer;
    t:tab;
procedure perm(var t:tab);
var wynik:tab;
uzyte:set of indeksy;

        procedure ala(k:integer);
        var i:integer;
        begin
                if k=n+1 then begin
                        for i:=1 to n do write(wynik[i],' ');
                        writeln
                end else for i:=1 to n do if not (i in uzyte) then begin
                        wynik[k]:=t[i];
                        uzyte:=uzyte+[i];
                        ala(k+1);
                        uzyte:=uzyte-[i]
                end
        end;
begin
        uzyte:=[];
        ala(1)
end;

begin
        for i:=1 to n do t[i]:=i;
        perm(t);
        readln
end.
