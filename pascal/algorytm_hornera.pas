const n=2;
type tab=array[0..n] of integer;
var x,i:integer;
    t:tab;

function horner(var t:tab; k:integer):integer;

begin
        if k=n then horner:=t[0]
        else horner:=t[k]+x*horner(t,k+1)
end;

begin
        read(x);
        for i:=0 to n do read(t[i]);
        write(horner(t,0));
        readln(x)
end.

