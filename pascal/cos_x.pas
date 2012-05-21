program cosx;
var
cos,m,x:real;
n:int64;

begin
read(x);
cos:=1.0;
n:=1;
m:=1.0;
repeat
  m:=m*(-1)*x*x/((2*n-1)*2*n);
  cos:=cos+m;
  inc(n);
until abs(m/cos)<1e-10;  write(n);
write(cos);
readln(n)
end.
