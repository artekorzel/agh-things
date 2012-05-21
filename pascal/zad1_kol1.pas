const n=10;
type tab=array[1..n] of integer;

function sprawdz(var t:tab):boolean;
var
i,a,b:integer;
b1,b2:boolean;

        function pierwsza(k:integer):boolean;
        var i:integer;
        begin
                pierwsza:=true;
                i:=2;
                while (pierwsza) and (i<=trunc(sqrt(k))) do begin
                        if k mod i = 0 then pierwsza:=false;
                        inc(i)
                end
        end;

begin
        b2:=false;
        b1:=true;
        a:=1;
        b:=2;

        if (pierwsza(t[a])) or (pierwsza(t[b])) then b1:=false;

        while (b1) and (a+b<=n) do begin
                b:=a+b;
                a:=b-a;
                i:=a+1;
                while (not b2) and (i<=b-1)do begin
                        if pierwsza(t[i]) then b2:=true;
                        inc(i)
                end;
                if pierwsza(t[b]) then b1:=false
        end;
        if (b1) and (b2) then sprawdz:=true
        else sprawdz:=false
end;

var t:tab;

begin
        t[1]:=4;
        t[2]:=6;
        t[3]:=8;
        t[4]:=5;
        t[5]:=5;
        t[6]:=4;
        t[7]:=4;
        t[8]:=10;
        t[9]:=4;
        t[10]:=4;
        if sprawdz(t) then write('tak')
        else write('nie');
        readln()
end.