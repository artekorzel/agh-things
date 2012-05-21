const n=5;
type tab=array[1..n] of integer;
var
t:tab;
c,i:integer;
procedure liczospr(var t:tab; var b:boolean);
var
i,a:integer;
begin
        for i:=1 to n do begin
                a:=0;
                while (t[i] > 0) do begin
                if t[i] mod 2 = 1 then inc(a);
                t[i]:=t[i] div 2
                end;
                t[i]:=a
        end;
        a:=0;
        b:=false;
        for i:=1 to n do a:=a+t[i];
        if a mod 3 = 0 then b:=true
end;

function sprawdz(var t:tab; m,s1,s2,s3:integer):boolean;
var
b:boolean;
begin
        liczospr(t,b);
        if (not b) then sprawdz:=false
        else begin
           if m>n then if ((s1=s2) and (s2=s3)) then sprawdz:=true
           else begin
                sprawdz(t,m+1,s1+t[m],s2,s3);
                sprawdz(t,m+1,s1,s2+t[m],s3);
                sprawdz(t,m+1,s1,s2,s3+t[m])
           end
        end;
        writeln(s1);
end;


begin
        while not eoln do begin
                for i:=1 to n do begin
                        read(c);
                        t[i]:=c
                end
        end;
        if sprawdz(t,0,0,0,0) then writeln('1');
end.
