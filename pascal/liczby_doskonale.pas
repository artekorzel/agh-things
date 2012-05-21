program liczbydoskonale;
var
n,i,k,g:int64;
begin
read(g);
n:=2;

while (n<g)  do
begin
i:=1;
k:=0;
        while(i*i<n) do
        begin
        if n mod i = 0 then
        begin
         if i<>1 then begin k:=k+i+(n div i); end
         else k:=k+i;
        end;
        inc(i);
        end;
        if i*i=n then k:=k+i;

if k=n then writeln(k);
inc(n);
end;
write('koniec');
read(i);
end.
