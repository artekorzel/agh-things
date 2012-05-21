const   max=5;
type
        punkt= record
                x,y:real;
                end;
        tab=array[1..max] of punkt;

function srodek(var t:tab; k:integer; r:real):boolean;
var
        b:boolean;
        n,j:integer;
        procedure ala(aktn,i:integer; xs,ys:real);
        begin
                if aktn=0 then begin
                        if (sqrt(sqr(xs)+sqr(ys))/n) < r then b:=true
                end else begin
                        for i:=i to max-aktn+1 do if i<=max then
                                ala(aktn-1,i+1,xs+t[i].x,ys+t[i].y)
                end
        end;
begin
        b:=false;
        j:=0;
        while (not b) and (n<k) do begin
                inc(j);
                n:=3*j;
                ala(n,1,0.0,0.0)
        end;
        srodek:=b;
end;

{dla sprawdzenia:}
var i,k:integer; t:tab; r:real;

begin
        for i:=1 to max do begin
                t[i].x:=i;
                t[i].y:=i
        end;
        readln(k,r);
        if srodek(t,k,r) then write('TAK') else write('NIE');
        readln
end.

