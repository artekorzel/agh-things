var n:integer;

procedure choineczka(k:integer);
var i:integer;
begin
        if k=1 then write('*')
        else begin
                write(' ');
                choineczka(k-1);
                writeln;
                for i:=1 to n-k do write(' ');
                for i:=1 to 2*k-1 do write('*')
        end
end;

begin
        readln(n);
        choineczka(n);
        readln
end.



