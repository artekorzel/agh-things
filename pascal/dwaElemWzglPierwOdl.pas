program dwaElemWzglPierwOdl;

const
max = 3;

type
tab = array [1..max, 1..max] of integer;

function nwd(a, b : integer) : integer;
var
c : integer;
begin
	if b = 0 then nwd := a
	else
	begin
		c := a mod b;
		a := b;
		b := c;
	end;
end;

function sprawdz(var t : tab) : boolean;
const
x : array[1..8] of integer = (1,2,2,1,-1,-2,-2,-1);
y : array[1..8] of integer = (2,1,-1,-2,-2,-1,1,2);
var
i, j, k, x2, y2 : integer;
nieznal : boolean;
begin
	j := 1;
	nieznal := false;
	while (j <= max) and (not nieznal) do
	begin
		i := 1;
		while (i <= max) and (not nieznal) do
		begin
			k := 1;
			while (k <= 8) and (not nieznal) do
			begin
				x2 := i + x[k];
				y2 := j + y[k];
				if (x2 in [1..max]) and (y2 in [1..max]) then if nwd(t[j,i], t[y2,x2]) = 1 then nieznal := true;
				inc(k);
			end;
			inc(i);
		end;
		inc(j);
	end;
	sprawdz := nieznal;
end;
var x:integer;
const
t : tab = ((5,10,20),(15,10,3),(5,3,15));
begin
writeln(sprawdz(t),nwd(15,3));
readln(x)
end.







