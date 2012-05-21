const   n=3;
        max=5;
        liczba=10;
type tab=array[1..max] of integer;
var t:tab;
i:integer;

procedure nka2(var t:tab; n,l:integer);
var licznik:integer;

 procedure wlasc(var licznik:integer; aktn,i,suma:integer);
 var j:integer;

 begin
        if aktn=1 then for j:=i to max do if t[j]=suma then inc(licznik)
        else
                for i:=i to max-aktn+1 do
                        wlasc(licznik,aktn-1,i+1,suma-t[i])
 end;

begin
        licznik:=0;
        wlasc(licznik,n,1,l);
        write(licznik)
end;


begin
        for i:=1 to max do t[i]:=i;
        nka2(t,n,liczba);
        readln
end.
