program Comb1;
const
    Max = 5;
type
    TIndex = 1..Max;
    TTab = array[TIndex] of Integer;
procedure Combinations( var a: TTab; l, n: integer);
var
    result: TTab;
procedure Combinations1( i, j: integer );
begin
    if i = n+1 then begin
	for j := 1 to n do Write( result[j], ' ' );
	Writeln
    end else
	for j := j to l do begin
	    result[i] := a[j];
	    Combinations1( i+1, j+1 );
	    if j - l > n - i then
		Combinations1( i, j+1 )
	end
end;

begin
    Combinations1( 1, 1 )
end;

const
    tab: TTab = (1, 2, 3, 4, 5);

begin
    Combinations( tab, 5, 3 );
    readln
end.
