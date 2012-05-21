const max=3;
type tab=array[1..max,1..max] of integer;

function sprawdz(var t:tab):boolean;
const
dx:array[0..3] of integer = (-2, -1, 1, 2);
dy:array[0..3] of integer = (1, 2, 2, 1);
var i,j,k,a,b:integer;

        function nwd(x,y:integer):integer;
        begin
                while (y<>0) do begin
                        nwd:=x mod y;
                        x:=y;
                        y:=nwd
                end;
                nwd:=x
        end;

begin
   sprawdz:=false;
   for i:=1 to max-1 do begin
        for j:=1 to max do begin
             for k:=0 to 3 do begin
                  a:=i+dy[k];
                  b:=j+dx[k];
                  if (a in [1..max]) and (b in [1..max]) then
                        if nwd(t[i,j],t[a,b])=1 then sprawdz:=true
             end
        end
   end
end;

var t:tab;
i,j:integer;
begin
        for i:=1 to max do for j:=1 to max do read(t[i,j]);
        if sprawdz(t) then writeln('tak')
        else writeln('nie');
        readln()
end.
