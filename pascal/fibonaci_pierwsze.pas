const n=10;

type tab=array[1..n] of integer;

var
t:tab;
c,i:integer;

procedure fibonaci(var f:tab);
var
i:integer;
begin
        i:=0;
        repeat
        inc(i);
        if (i in [1,2]) then f[i]:=i
        else f[i]:=f[i-1]+f[i-2];
        until f[i]>=n;
        for i:=i to n do f[i]:=0;

end;

function czypierwsza(a:integer):boolean;
var i:integer;
begin
        czypierwsza:=false;
        for i:=2 to trunc(sqrt(a)) do begin
                if a mod i = 0 then begin
                        czypierwsza:=true;
                        break
                end
        end;
        if a in [2,3] then czypierwsza:=true
end;

function sprawdz(var t:tab):boolean;
var
f:tab;
a,b:boolean;
z,x:integer;
begin
        a:=false;
        b:=true;
        sprawdz:=false;
        fibonaci(f);
        x:=0;
        while x<=n do begin
                inc(x);
                for z:=1 to n do begin
                        if (f[x]=z) then begin
                                if czypierwsza(t[z])=true then begin
                                        b:=false;
                                        break
                        end else begin
                                if czypierwsza(t[z])=true then begin
                                        a:=true;
                                        break
                                end
                        end
                        end
                end;
                if ((a) or (not b)) then break
        end;
        if ((a) and (b)) then sprawdz:=true
end;

begin
        while not eoln do begin
                for i:=1 to n do begin
                        read(c);
                        t[i]:=c
                end
        end;
        for i:=1 to n do
                write(t[i],' ');
        writeln();
        if sprawdz(t)=true then write('1')
        else write('0');
        readln(c)

end.
