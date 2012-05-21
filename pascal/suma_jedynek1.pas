const n=3;
type tab=array[1..n]of integer;

var bool:boolean;
tabl:tab;
i:integer;

procedure jedynki(var t:tab);
var
i,k:integer;
begin
        for i:=1 to n do begin
                k:=0;
                while (t[i]<>0) do begin
                        if (t[i] mod 2 = 1) then inc(k);
                        t[i]:=t[i] div 2
                end;
                t[i]:=k
        end
end;

procedure sprawdz(var t:tab; s1,s2,s3,k:integer; var b:boolean);
begin
        if (k>n) then begin
                if (s1=s2) and (s2=s3) then b:=true
        end else begin
                sprawdz(t,s1+t[k],s2,s3,k+1,bool);
                sprawdz(t,s1,s2+t[k],s3,k+1,bool);
                sprawdz(t,s1,s2,s3+t[k],k+1,bool);
        end
end;

begin
        for i:=1 to n do read(tabl[i]);
        jedynki(tabl);
        bool:=false;
        sprawdz(tabl,0,0,0,1,bool);
        if bool then write('tak') else write('nie');
        readln(i)
end.