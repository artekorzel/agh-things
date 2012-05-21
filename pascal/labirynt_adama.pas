const   max=5;
type    tab=array[1..max,1..max] of integer;
var
t:tab;
i,j:integer;

procedure wypisz();
var i,j:integer;
begin
	for i := 1 to max do begin
		for j := 1 to max do begin
			if t[i][j] = 0 then write('0');
			if t[i][j] = 1 then write ('x');
			if t[i][j] > 1 then write(t[i][j]-1);
		end;
		writeln();
	end;
	writeln();
end;
 
function labi(var t:tab; i,j,k:integer):boolean;
var
b:boolean;
begin
	b := false;
	t[i][j] := 0;
	if k < max*max then begin
		if (i=max) and (j = max) then b:= true else begin 
			if (i+1 <= max) and (t[i+1][j] = 1) then b := labi(t,i+1,j,k+1);
			if (not b) and (j + 1 <= max) and (t[i][j+1] = 1) then b := labi(t,i,j+1,k+1);
			if (not b) and (i - 1 > 0) and (t[i-1][j] = 1) then b := labi(t,i-1,j,k+1);
			if (not b) and (j - 1 > 0) and (t[i][j-1] = 1) then b := labi(t,i,j-1,k+1);
		end;
		if b then t[i][j] := k else t[i][j] := 1;
	end;
	labi := b;
end;
 
begin
	Randomize();
        for i:=1 to max do for j:=1 to max do t[i,j]:=random(2);
	t[1][1] := 1;
	t[max][max] := 1;
	wypisz();
	if labi(t,1,1,2) then wypisz() else writeln('Lipa');
	readln();
end.