var n:integer;

procedure choineczka(k:integer);
var i:integer;
begin
        repeat
                for i:=1 to n-k do write(' ');
                for i:=1 to 2*k-1 do write('*');
                writeln;
                inc(k)
        until k>n
end;

begin
        readln(n);
        choineczka(1);
        readln
end.



