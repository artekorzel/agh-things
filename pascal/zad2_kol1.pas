const n=5;
type tab=array[1..n] of integer;
var j:integer;
    t:tab;
function czypodzieli(t:tab):boolean;
var b:boolean;

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
        var i,tmp:integer;
        begin
            if (not b) then begin
                if (k=n) then begin
                        if (s1=s2) and (s2=s3) then b:=true
                end else
                        for i:=1 to n do if (t[i]<>0) then begin
                                tmp:=t[i]; t[i]:=0;
                                ala(t,s1+tmp,s2,s3,k+1);
                                ala(t,s1,s2+tmp,s3,k+1);
                                ala(t,s1,s2,s3+tmp,k+1);
                                t[i]:=tmp
                        end
            end
        end;

begin
        jedynki(t);
        b:=false;
        ala(t,0,0,0,0);
        czypodzieli:=b
end;

begin
        for j:=1 to n do read(t[j]);
        if czypodzieli(t) then writeln('tak') else writeln('nie');
        readln();
end.
