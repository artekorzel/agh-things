const n=5;
      k=3;
type  tab=array[1..n] of integer;
var   wynik:tab;
procedure kom(var t:tab; aktn,aktk:integer);
var i,tmp:integer;
begin
        if aktk=k+1 then begin
                for i:=1 to k do write(wynik[i], ' ');
                writeln
        end else
                for aktn:=1 to n do
                   if t[aktn]<>0 then begin
                        tmp:=t[aktn];
                        wynik[aktk]:=tmp;
                        t[aktn]:=0;
                        kom(t,aktn+1,aktk+1);
                        t[aktn]:=tmp;

                   end
end;

const t:tab=(1,2,3,4,5);

begin
        kom(t,1,1);
        readln
end.

