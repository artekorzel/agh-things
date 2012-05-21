var a:integer;

function sprawdz(wejscie:string):boolean;
var
        bool:boolean;
        i,j,k,a,max:integer;

begin
        sprawdz:=false;
        max:=length(wejscie);
        i:=2;

        while (i<=max) and (not sprawdz) do begin
           if (max mod i=0) then begin
                a:=max div i;
                bool:=true;
                j:=1;
                while (j<=a) and (bool) do begin
                        k:=1;
                        while (k<=i-1) and (bool) do begin
                                if (wejscie[j]<>wejscie[j+k*a]) then bool:=false;
                                inc(k);
                        end;
                        inc(j);
                end;
                if bool then sprawdz:=true;
           end;
           inc(i);
        end;
end;

begin
        if sprawdz('abcabcabc') then write('tak') else write('nie');
        readln(a);
end.
