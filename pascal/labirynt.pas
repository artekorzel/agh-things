const   max=4;
type    tab=array[1..max,1..max] of boolean;
        tab2=array[1..2,1..max*max] of integer;
var
        t:tab;
        t2:tab2;
        i,j,a:integer;
        bool:boolean;


procedure labi(var t:tab; var t2:tab2; i,j,k:integer; var bool:boolean);
var
        b:boolean;
        a:integer;

        procedure wypisz(var t:tab; var t2:tab2);
        var
        a,b,i,j:integer;
        begin
                a:=max*max;
                while (t2[1,a]=0) do dec(a);
                for i:=1 to max do begin
                        for j:=1 to max do begin
                                if t[i,j] then begin
                                    for b:=1 to a do
                                        if (i=t2[1,b]) and (j=t2[2,b]) then write(b:3)
                                end else write('0':3)
                        end;
                        writeln
                end;
                writeln
        end;


begin
        if (i=max) and (j=max) then begin
                t2[1,k]:=i;
                t2[2,k]:=j;
                bool:=true;
                wypisz(t,t2)
        end else if k=max*max then bool:=false
        else begin
                if (i-1 in [1..max]) then if t[i-1,j] then begin
                   b:=false;
                   for a:=1 to k-1 do if (t2[1,a]=i-1) and (t2[2,a]=j) then b:=true;
                   if not b then begin
                        t2[1,k]:=i;
                        t2[2,k]:=j;
                        labi(t,t2,i-1,j,k+1,bool)
                   end
                end;
                if (i+1 in [1..max]) then if t[i+1,j] then begin
                   b:=false;
                   for a:=1 to k-1 do if (t2[1,a]=i+1) and (t2[2,a]=j) then b:=true;
                   if not b then begin
                        t2[1,k]:=i;
                        t2[2,k]:=j;
                        labi(t,t2,i+1,j,k+1,bool)
                   end
                end;
                if (j-1 in [1..max]) then if t[i,j-1] then begin
                   b:=false;
                   for a:=1 to k-1 do if (t2[1,a]=i) and (t2[2,a]=j-1) then b:=true;
                   if not b then begin
                        t2[1,k]:=i;
                        t2[2,k]:=j;
                        labi(t,t2,i,j-1,k+1,bool)
                   end
                end;
                if (j+1 in [1..max]) then if t[i,j+1] then begin
                   b:=false;
                   for a:=1 to k-1 do if (t2[1,a]=i) and (t2[2,a]=j+1) then b:=true;
                   if not b then begin
                        t2[1,k]:=i;
                        t2[2,k]:=j;
                        labi(t,t2,i,j+1,k+1,bool)
                   end
                end
        end
end;

begin
       { for i:=1 to max do for j:=1 to max do t[i,j]:=false;
        for i:=1 to max do t[1,i]:=true;
        for i:=2 to max do t[i,max]:=true;}
        for i:=1 to max*max do begin
                t2[1,i]:=0;
                t2[2,i]:=0
        end;
        for i:=1 to max do for j:=1 to max do t[i,j]:=true;

        bool:=false;
        labi(t,t2,1,1,1,bool);
        if not bool then writeln('NIE MA');
        readln
end.

