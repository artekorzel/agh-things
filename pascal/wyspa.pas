const max=6;
type tab=array[1..max,1..max] of boolean;
var t:tab;
x,y,a:integer;
function zatop(var t:tab; x,y:integer):integer;
var licznik:integer;
procedure top(x,y:integer);
begin
        if t[x,y] then begin
                t[x,y]:=false;
                inc(licznik);
                if (x-1 in [1..max]) then top(x-1,y);
                if (x+1 in [1..max]) then top(x+1,y);
                if (y-1 in [1..max]) then top(x,y-1);
                if (y+1 in [1..max]) then top(x,y+1)
        end
end;

begin
        licznik:=0;
        top(x,y);
        zatop:=licznik
end;

begin
        randomize;
        for x:=1 to max do for y:=1 to max do begin
                a:=random(2);
                if a=0 then t[x,y]:=false
                else t[x,y]:=true
        end;
        for x:=1 to max do begin
                for y:=1 to max do begin
                        if t[x,y] then write('1':2)
                        else write('0':2)
                end;
                writeln
        end;
        readln(x,y);
        writeln(zatop(t,x,y));
        for x:=1 to max do begin
                for y:=1 to max do begin
                        if t[x,y] then write('1':2)
                        else write('0':2)
                end;
                writeln
        end;
        readln
end.



