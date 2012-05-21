const max=8;
type szachy=array[1..max,1..max] of integer;

var
t1:szachy;
i,j:integer;
a:boolean;
function szach(var t:szachy):boolean;
var
i,j,k,a,b,c,d:integer;
sz:boolean;
begin
        sz:=false;
        for i:=1 to max do begin
                for j:=1 to max do begin
                        if (t[i,j] in [1..max-1]) then begin
                                a:=i-t[i,j];
                                b:=i+t[i,j];
                                c:=j-t[i,j];
                                d:=j+t[i,j];

                                for k:=c to d do begin
                                        if ((c in [1..max]) and (d in [1..max])) then begin;
                                                if (a in [1..max]) then if t[a,k]=t[i,j] then sz:=true;
                                                if ((b in [1..max]) and not sz) then if t[b,k]=t[i,j] then sz:=true;
                                        end
                                end;

                             if not sz then
                                for k:=a to b do begin
                                        if ((a in [1..max]) and (b in [1..max])) then begin;
                                                if (c in [1..max]) then if t[c,k]=t[i,j] then sz:=true;
                                                if (d in [1..max]) then if t[d,k]=t[i,j] then sz:=true;
                                        end
                                end;
                        end;

                        if sz then break
                end;

                if sz then break
        end;
        szach:=sz;
end;

begin
        randomize;
        for i:=1 to max do for j:=1 to max do t1[i,j]:=random(10)+1;
        for i:=1 to max do begin
                for j:=1 to max do
                        write(t1[i,j],' ');
                writeln()
        end;
        a:=szach(t1);
        if a then write('1') else write('0');
        readln()
end.




