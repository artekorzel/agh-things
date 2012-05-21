const n=6;
type tab=array [1..n] of integer;
var
t:tab=(1,2,3,4,5,6);

function silnia(n:integer):integer;
begin
        if n=1 then silnia:=1
        else silnia:=n*silnia(n-1)
end;


procedure wariacja(var t:tab;k:integer);


        procedure mieszaj(var t:tab);
        var
        j,l:integer;

        begin
                for l:=1 to k do begin
                        for j:=l to k do write(t[j],' ');
                        for j:=1 to l-1 do write(t[j],' ');
                        writeln
                end
        end;

   procedure zamieniaj(var t:tab);
   var
   i,a:integer;
   begin
        for i:=0 to silnia(k-1)-1 do begin
           if i<k-1 then begin
                a:=t[1+i];
                t[1+i]:=t[2+i];
                t[2+i]:=a;
                mieszaj(t)
           end else if i=k-1 then begin
                a:=t[k];
                t[k]:=t[1];
                t[1]:=a;
                mieszaj(t)
           end else begin
                a:=t[i div k];
                t[i div k]:=t[i div k + 1];
                t[i div k + 1]:=a;
                mieszaj(t)
           end
        end;
   end;

begin
        zamieniaj(t);
end;

begin
        wariacja(t,4);
        readln();
end.


