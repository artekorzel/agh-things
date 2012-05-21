program dw;
type dt=(pon,wt,sr,czw,pt,so,nd);
var
d,m,r,a,b,e:integer;
t:array[1..31,1..12,1..4000]of dt;
z:dt;

begin

write('dzien:');
readln(d);
write('miesiac:');
readln(m);
write('rok:');
readln(r);

b:=1;
z:=so;
for  a:=1 to 4000 do begin
 for b:=1 to 12 do begin
  if (b=1) or (b=3) or (b=5) or (b=7) or (b=8) or (b=10) or (b=12) then
    for e:=1 to 31 do begin t[a,b,e]:=z; end;
  if (b=4) or (b=6) or (b=9) or (b=11) then
    for e:=1 to 30 do begin t[a,b,e]:=z; end;
  if b=2 then begin
    if (a mod 4 = 0) or (a mod 100 = 0) then
        for e:=1 to 29 do begin
             t[a,b,e]:=z; end
    else for e:=1 to 28 do begin
             t[a,b,e]:=z; end
  end
 end
end;
write('bedzie wtedy ');
readln()
end.
