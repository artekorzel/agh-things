program armstronga;
var
dwa:array[1..20]of byte;
trzy:array[1..30]of byte;
cztery:array[1..40]of byte;
piec:array[1..45]of byte;
szesc:array[1..50]of byte;
siedem:array[1..55]of byte;
osiem:array[1..57]of byte;
dziewiec:array[1..60]of byte;
t,p:array[1..61]of byte;
b:boolean;
i,l,j,q,c,k,m:byte;
begin

 dwa[1]:=1; for i:=2 to 20 do t[i]:=0;
 trzy[1]:=1; for i:=2 to 30 do t[i]:=0;
 cztery[1]:=1; for i:=2 to 40 do t[i]:=0;
 piec[1]:=1; for i:=2 to 45 do t[i]:=0;
 szesc[1]:=1; for i:=2 to 50 do t[i]:=0;
 siedem[1]:=1; for i:=2 to 55 do t[i]:=0;
 osiem[1]:=1; for i:=2 to 57 do t[i]:=0;
 dziewiec[1]:=1; for i:=2 to 60 do t[i]:=0;
 for i:=2 to 61 do t[i]:=0;
 t[1]:=1;
 k:=0;


 repeat

  m:=0;
  j:=60;
  while(t[j]=0) do dec(j);

  t[61]:=0;
  for i:=1 to j do begin
   dwa[i]:=dwa[i]*2+t[61];;
   t[61]:=dwa[i] div 10;
   dwa[i]:=dwa[i] mod 10;
  end;
  t[61]:=0;
  for i:=1 to j do begin
   trzy[i]:=trzy[i]*3+t[61];
   t[61]:=trzy[i] div 10;
   trzy[i]:=trzy[i] mod 10;
  end;
  t[61]:=0;
  for i:=1 to j do begin
   cztery[i]:=cztery[i]*4+t[61];
   t[61]:=cztery[i] div 10;
   cztery[i]:=cztery[i] mod 10;
  end;
  t[61]:=0;
  for i:=1 to j do begin
   piec[i]:=piec[i]*5+t[61];
   t[61]:=piec[i] div 10;
   piec[i]:=piec[i] mod 10;
  end;
  t[61]:=0;
  for i:=1 to j do begin
   szesc[i]:=szesc[i]*6+t[61];
   t[61]:=szesc[i] div 10;
   szesc[i]:=szesc[i] mod 10;
  end;
  t[61]:=0;
  for i:=1 to j do begin
   siedem[i]:=siedem[i]*7+t[61];
   t[61]:=siedem[i] div 10;
   siedem[i]:=siedem[i] mod 10;
  end;
  t[61]:=0;
  for i:=1 to j do begin
   osiem[i]:=osiem[i]*8+t[61];
   t[61]:=osiem[i] div 10;
   osiem[i]:=osiem[i] mod 10;
  end;
  t[61]:=0;
  for i:=1 to j do begin
   dziewiec[i]:=dziewiec[i]*9+t[61];
   t[61]:=dziewiec[i] div 10;
   dziewiec[i]:=dziewiec[i] mod 10;
  end;

 repeat

  inc(m);
  for i:=1 to j do p[i]:=0;
  for i:=1 to j do begin
   if t[i]=1 then begin
    p[1]:=p[1]+1;
    q:=p[1] div 10;
    p[1]:=p[1] mod 10;
    for l:=1 to j do begin
     p[l]:=p[l]+q;
     q:=p[l] div 10;
     p[l]:=p[l] mod 10;
    end;
   end;
   if t[i]=2 then begin
    q:=0;
    for l:=1 to j do begin
     p[l]:=p[l]+q+dwa[i];
     q:=p[l] div 10;
     p[l]:=p[l] mod 10;
    end;
   end;
   if t[i]=3 then begin
    q:=0;
    for l:=1 to j do begin
     p[l]:=p[l]+q+trzy[i];
     q:=p[l] div 10;
     p[l]:=p[l] mod 10;
    end;
   end;
   if t[i]=4 then begin
    q:=0;
    for l:=1 to j do begin
     p[l]:=p[l]+q+cztery[i];
     q:=p[l] div 10;
     p[l]:=p[l] mod 10;
    end;
   end;
   if t[i]=5 then begin
    q:=0;
    for l:=1 to j do begin
     p[l]:=p[l]+q+piec[i];
     q:=p[l] div 10;
     p[l]:=p[l] mod 10;
    end;
   end;
   if t[i]=6 then begin
    q:=0;
    for l:=1 to j do begin
     p[l]:=p[l]+q+szesc[i];
     q:=p[l] div 10;
     p[l]:=p[l] mod 10;
    end;
   end;
   if t[i]=7 then begin
    q:=0;
    for l:=1 to j do begin
     p[l]:=p[l]+q+siedem[i];
     q:=p[l] div 10;
     p[l]:=p[l] mod 10;
    end;
   end;
   if t[i]=8 then begin
    q:=0;
    for l:=1 to j do begin
     p[l]:=p[l]+q+osiem[i];
     q:=p[l] div 10;
     p[l]:=p[l] mod 10;
    end;
   end;
   if t[i]=9 then begin
    q:=0;
    for l:=1 to j do begin
     p[l]:=p[l]+q+dziewiec[i];
     q:=p[l] div 10;
     p[l]:=p[l] mod 10;
    end;
   end;
  end;

  b:=true;
   for i:=1 to j do begin if t[i]<>p[i] then begin b:=false; break; end; end;
   if b then begin
    inc(k);
    write('     liczba nr ',k,':     ');
    for i:=j downto 1 do write(t[i]);
    writeln();
   end;

  t[61]:=0;

  c:=0;
  t[1]:=t[1] + 1;
   for i:=1 to j+1 do begin
    t[i]:=t[i]+c;
    c:=t[i] div 10;
    t[i]:=t[i] mod 10;
    end;
 until(m=10);
 until(t[61]=1);
end.




