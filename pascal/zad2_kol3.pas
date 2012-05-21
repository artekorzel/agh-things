function zlozona(x:integer):boolean;
var c:integer;

begin
        c:=2;
        zlozona:=false;
        while (not zlozona) and (c<=trunc(sqrt(x))) do begin
                if x mod c = 0 then zlozona:=true;
                inc(c)
        end
end;


function ile(a,b:integer):integer;

        procedure ala(i,j,liczba:integer);

        begin
                if (i=0) and (j=0) then begin
                        if zlozona(liczba) then inc(ile)
                end else begin
                        if i>0 then ala(i-1,j,liczba*2+1);
                        if j>0 then ala(i,j-1,liczba*2)
                end
        end;

begin
        ile:=0;
        ala(a-1,b,1);
end;

var y:integer;

begin
        writeln(ile(3,2));
        readln(y)
end.
