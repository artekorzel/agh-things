const   n=25;
type    tab=array[1..n]of integer;
var     t:tab;
        i:integer;
procedure rozklad(var t:tab; k,i,nrel:integer);

        procedure wypisz(var t:tab);
        var a,i:integer;
        begin
                a:=n;
                while(t[a]=0) do dec(a);
                for i:=1 to a-1 do write(t[i],'+');
                writeln(t[a]);
        end;


begin
        if k=n then wypisz(t)
        else if k<n then
                for i:=i to n-1 do begin
                        t[nrel]:=i;
                        rozklad(t,k+i,i,nrel+1);
                        t[nrel]:=0
                end
end;

begin
        for i:=1 to n do t[i]:=0;
        rozklad(t,0,1,1);
        readln
end.
