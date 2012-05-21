const max=8;
type tab=array[1..max,1..max] of boolean;
var t:tab;
i,j,k:integer;
procedure hetman(var t:tab; n:integer; var k:integer);
var
i,j,dd,a,b,c,d:integer;
bool:boolean;
begin
        if n=0 then begin
           inc(k);
           writeln('liczba = ',k);
           for i:=1 to max do begin
                for j:=1 to max do begin
                        if t[i,j] then write('1':3)
                        else write('0':3);
                end;
                writeln
           end;
           writeln
        end else
               { for i:=max-n+1 to max do}
               i:=max-n+1;
               for j:=1 to max do
                   if not t[i,j] then begin
                        bool:=false;
                        for dd:=-max+1 to max-1 do if dd<>0 then begin
                                a:=i-dd;
                                b:=i+dd;
                                c:=j-dd;
                                d:=j+dd;

                                if (a in [1..max]) then if t[a,j] then bool:=true;
                                if not bool then if (b in [1..max]) then if t[b,j] then bool:=true;
                                if not bool then if (c in [1..max]) then if t[i,c] then bool:=true;
                                if not bool then if (d in [1..max]) then if t[i,d] then bool:=true;
                                if not bool then if (a in [1..max]) and (c in [1..max]) then if t[a,c] then bool:=true;
                                if not bool then if (a in [1..max]) and (d in [1..max]) then if t[a,d] then bool:=true;
                                if not bool then if (b in [1..max]) and (c in [1..max]) then if t[b,c] then bool:=true;
                                if not bool then if (b in [1..max]) and (d in [1..max]) then if t[b,d] then bool:=true;
                                if bool then break
                        end;
                        if (not bool) then begin
                                        t[i,j]:=true;
                                        hetman(t,n-1,k);
                                        t[i,j]:=false
                        end
                   end
end;

begin
        for i:=1 to max do for j:=1 to max do t[i,j]:=false;
        k:=0;
        hetman(t,8,k);
        readln
end.


