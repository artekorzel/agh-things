const n=5;
type tab=array[1..n] of integer;
var j:integer;
    t:tab;
function czypodzieli(t:tab):integer;

        procedure jedynki(var t:tab);
        var
                i,tmp:integer;
        begin
                for i:=1 to n do begin
                        tmp:=t[i];
                        t[i]:=0;
                        while (tmp<>0) do begin
                                if tmp mod 2 = 1 then inc(t[i]);
                                tmp:=tmp div 2
                        end;
                end;
        end;

        procedure ala(var t:tab; s1,s2,s3,k:integer);

        begin
                if (k=n+1) then begin
                        if (s1=s2) and (s2=s3) then inc(czypodzieli)
                end else begin
                        ala(t,s1+t[k],s2,s3,k+1);
                        ala(t,s1,s2+t[k],s3,k+1);
                        ala(t,s1,s2,s3+t[k],k+1);
                end
        end;

begin
        jedynki(t);
        czypodzieli:=0;
        ala(t,0,0,0,1);
        czypodzieli:=czypodzieli div 6
end;

begin
        for j:=1 to n do read(t[j]);
        write(czypodzieli(t));
        readln(j);
end.
