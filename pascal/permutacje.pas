const n=3;
type tab=array[1..n] of integer;
var t:tab; i:integer;

procedure permutuj(var x:tab; l:integer);
var tmp:array[1..n] of integer;
j:integer;
begin
        if l=0 then begin
                for j:=1 to l do write(tmp[j]);
                writeln
        end else
                for l:=l downto 1 do begin
                        tmp[l]:=x[l];
                        permutuj(x,l-1)
                end
end;

begin
        for i:=1 to n do t[i]:=i;
        permutuj(t,n);
        readln
end.