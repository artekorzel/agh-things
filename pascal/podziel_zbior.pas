const   max=3;
        n=3;

type tab=array[1..max] of integer;
var
t:tab;
i,suman:integer;

function podziel(var t:tab; var suman:integer; k,i,aktsum:integer):boolean;
var
tmp:integer;
begin
        if k=0 then begin
                if aktsum=0 then podziel:=true
                else podziel:=false
        end else begin
                if aktsum=suman then podziel(t,suman,k-1,1,0)
                else if aktsum<suman then begin
                        for i:=i to max do begin
                                tmp:=t[i];
                                aktsum:=aktsum+t[i];
                                t[i]:=0;
                                podziel(t,suman,k,i+1,aktsum);
                                t[i]:=tmp;
                                aktsum:=aktsum-t[i]
                        end
                end;
                podziel:=false
        end
end;

begin
        suman:=0;
        for i:=1 to max do begin
                t[i]:=i;
                suman:=suman+t[i];
        end;
        if suman mod n = 0 then begin
                suman:=suman div n;
                if podziel(t,suman,n,1,0) then write('TAK, suma = ',suman)
                else write('NIE')
        end else write('NIE');
        readln
end.


