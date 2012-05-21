const   m=8;
        n=6;

var     najmn:integer;
        t:array[1..n]of integer;

function odwaz(s1,s2,ob,ind:integer):integer;
begin
       { writeln(s1,' ', s2);}
        if (s1=s2) then begin
                if ob<najmn then najmn:=ob
        end else if ind<=n then for ind:=ind to n do begin
                odwaz(s1,s2+t[ind],ob+1,ind+1);
                odwaz(s1+t[ind],s2,ob+1,ind+1);
        end;
     if najmn>n then odwaz:=0
     else odwaz:=najmn
end;

begin
        for najmn:=1 to n do read(t[najmn]);
        najmn:=n+1;
        writeln(odwaz(m,0,0,1));
        read(najmn)
end.
