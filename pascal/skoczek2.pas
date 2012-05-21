const max=8;
type
        tab=array[1..max,1..max] of integer;
        tab2=array[1..8] of integer;
var t:tab;
c,d:integer;




procedure sprawdz (w,k,i:integer; var nw,nk:integer; var b:boolean);
const
        dx:tab2=(1,2,2,1,-1,-2,-2,-1);
        dy:tab2=(-2,-1,1,2,2,1,-1,-2);

begin
        nk:=k+dx[i];
        nw:=w+dy[i];
        if ((nk in [1..max]) and (nw in [1..max]) and (t[nw,nk]=0)) then b:=true
        else b:=false
end;

procedure wypisz();
var
i,j:integer;
begin
        for i:=1 to max do begin
                for j:=1 to max do write(t[i,j]:4);
                writeln
        end;
        writeln
end;

procedure skok(w,k,n:integer);
var
i,nw,nk:integer;
b:boolean;
begin
        t[w,k]:=n;
        if n=max*max then wypisz()
        else begin

                for i:=1 to 8 do begin
                        sprawdz(w,k,i,nw,nk,b);
                        if b then skok(nw,nk,n+1)
                end;

        end;
        t[w,k]:=0
end;



begin
        for c:=1 to max do begin
                for d:=1 to max do begin
                        t[c,d]:=0;
                end;
        end;
        skok(1,1,1);

        readln();
end.
