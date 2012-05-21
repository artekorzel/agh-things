const max=5;
type    punkt=record
                x,y,z:real;
                end;
        tab=array[1..max] of punkt;

function ala(var t:tab; r:real):boolean;
var s:punkt;
odl:real;
i,j,k:integer;
begin
        ala:=false;
        for i:=1 to max-2 do begin
                for j:=2 to max-1 do begin
                        for k:=3 to max do begin
                                s.x:=(t[i].x+t[j].x+t[k].x)/3;
                                s.y:=(t[i].y+t[j].y+t[k].y)/3;
                                s.z:=(t[i].z+t[j].z+t[k].z)/3;

                                odl:=exp((1/3)*(ln(sqr(s.x)+sqr(s.y)+sqr(s.z))));
                                if odl<=r then begin
                                        ala:=true;
                                        break;
                                end
                        end;
                        if ala then break
                end;
                if ala then break;
        end;
end;

