program Var2;

const
    Max = 7;
type
    TIndex = 1..Max;
    TTab = array[TIndex] of Integer;

procedure Variations( var a: TTab; l, n: TIndex);
procedure Variations1( i: TIndex );
var
    j, tmp: TIndex;
begin
    if i = n+1 then begin
        for j := 1 to n do Write( a[j], ' ' );
        Writeln
    end else
	for j := i to l do begin
	    tmp := a[i];
    	    a[i] := a[j];
	    a[j] := tmp;
	    Variations1( i+1 );
	    tmp := a[i];
	    a[i] := a[j];
	    a[j] := tmp
	end
end;

begin
    Variations1( 1 )
end;

const
    tab: TTab = (1, 2, 3, 4, 5, 6, 7);

begin
    Variations( tab, 7, 3 );
    readln
end.
