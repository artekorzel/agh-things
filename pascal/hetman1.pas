const max=8;
type tab=array[1..max,1..max] of boolean;
var t:tab;
i,j:integer;
procedure hetman(var t:tab; n:integer);
var
i,j,dd,a,b,c,d:integer;
bool,sasiad:boolean;
begin
        if n=0 then begin
           for i:=1 to max do begin
                for j:=1 to max do begin
                        if t[i,j] then write('1':3)
                        else write('0':3);
                end;
                writeln
           end;
           writeln
        end else
                for i:=1 to max do for j:=1 to max do
                   if not t[i,j] then begin
                        sasiad:=false;
                        a:=i+1;
                        b:=i-1;
                        c:=j+1;
                        d:=j-1;
                        if (a in [1..max]) then if t[a,j] then sasiad:=true;
                        if not sasiad then if (b in [1..max]) then if t[b,j] then sasiad:=true;
                        if not sasiad then if (c in [1..max]) then if t[i,c] then sasiad:=true;
                        if not sasiad then if (d in [1..max]) then if t[i,d] then sasiad:=true;
                        bool:=false;
                        if not sasiad then for dd:=-max+1 to max-1 do if dd<>0 then begin
                                a:=i-dd;
                                b:=i+dd;
                                c:=j-dd;
                                d:=j+dd;

                                if (a in [1..max]) and (c in [1..max]) then if t[a,c] then bool:=true;
                                if not bool then if (a in [1..max]) and (d in [1..max]) then if t[a,d] then bool:=true;
                                if not bool then if (b in [1..max]) and (c in [1..max]) then if t[b,c] then bool:=true;
                                if not bool then if (b in [1..max]) and (d in [1..max]) then if t[b,d] then bool:=true;
                                if bool then break
                        end;
                        if (not sasiad) and (not bool) then begin
                                        t[i,j]:=true;
                                        hetman(t,n-1);
                                        t[i,j]:=false
                        end
                   end
end;

begin
        for i:=1 to max do for j:=1 to max do t[i,j]:=false;
        hetman(t,13);
        readln
end.


