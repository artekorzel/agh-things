program Var1;
const
    Max = 5;
type
    TIndex = 1..Max;
    TTab = array[TIndex] of Integer;

procedure Variations( var a: TTab; l, n: TIndex);
var
    result: TTab;
    used: set of TIndex;
procedure Variations1( i: TIndex );
var
    j: TIndex;
begin
    if i = n+1 then begin
	for j := 1 to n do Write( result[j], ' ' );
	Writeln
    end else
	for j := 1 to l do
	    if not (j in used) then begin
		used := used + [j];
		result[i] := a[j];
		Variations1( i+1 );
		used := used - [j];
	    end
end;

begin
    used := [];
    Variations1( 1 )
end;

const
    tab: TTab = (1, 2, 3, 4, 5);

begin
    Variations( tab, 5, 3 );
    readln
end.
