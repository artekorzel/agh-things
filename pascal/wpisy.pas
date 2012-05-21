const max = 10;

type tab=array[1..max] of integer;

var
i,k,a:integer;
t:tab;
b:boolean;

begin
        for i:=1 to max do t[i]:=0;
        while not eoln do begin
                read(a);
                k:=1;
                for i:=1 to max-1 do
                        if t[k]>t[i+1] then k:=i+1;
                b:=true;
                for i:=1 to max do begin
                        if a=t[i] then begin
                                b:=false;
                                break
                        end
                end;
                if (b) and (a>t[k]) then t[k]:=a
        end;
        for i:=1 to max do write(t[i],' ');
        readln()
end.