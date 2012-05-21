const n=6;
type    tab=array[1..n] of integer;
        tab2=array[1..n] of boolean;
var t:tab;
    i:integer;
function suma(var t:tab):integer;
var b:tab2;
    i,k:integer;
        function dziesiatkowy(a:integer):integer;
        var i:integer;
        begin
                i:=0;
                dziesiatkowy:=0;
                while (a<>0) do begin
                        dziesiatkowy:= (dziesiatkowy) + ((a mod 10) * trunc(exp(ln(7)*i)));
                        a:=a div 10;
                        inc(i)
                end
        end;

begin
        for i:=2 to n do b[i]:=true;
        b[1]:=false;
        for i:=2 to trunc(sqrt(n)) do if b[i] then begin
                for k:=2 to trunc(n/i) do b[k*i]:=false
        end;

        suma:=0;

        for i:=1 to n do
                if (not b[i]) then
                        suma:=suma + dziesiatkowy(t[i])
end;

begin
        for i:=1 to n do read(t[i]);
        write(suma(t));
        readln()
end.