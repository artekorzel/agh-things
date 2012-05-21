const n=5;
type tab=array[1..n] of integer;
var t:tab;
x:integer;

function ala(var t:tab;s1,s2,k:integer):boolean;

begin
        if k=n+1 then begin if s1=s2 then ala:=true else ala:=false end
        else ala:=ala(t,s1+t[k],s2,k+1) or ala(t,s1,s2+t[k],k+1)
end;

begin
        for x:=1 to n do read(t[x]);
        if ala(t,0,0,1) then write('tak') else write('nie');
        readln(x)
end.