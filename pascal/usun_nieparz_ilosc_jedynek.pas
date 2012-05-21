type    pnode=^node;
        node=record
               w:integer;
               next:pnode;
               end;

function ilosc1(k:integer):integer;
var a:integer;
begin
        a:=0;
        while k<>0 do begin
                a:=a + k mod 2;
                k:=k div 2
        end;
        ilosc1:=a
end;

procedure usun(var f:pnode);
var
p,q:pnode;
begin
        q:=f;
        if q<> nil then begin
                p:=q^.next;
                while p<>nil do begin
                        if ilosc1(p^.w) mod 2 =1 then begin
                                q^.next:=p^.next;
                                dispose(p);
                                p:=q^.next
                        end else begin
                                q:=p;
                                p:=p^.next
                        end
                end;
                if ilosc1(f^.w) mod 2 = 1 then begin
                        q:=f;
                        f:=f^.next;
                        dispose(q)
                end
        end
end;

procedure tworz(var f:pnode);
var p,q:pnode;
i:integer;
begin
        new(f);
        read(f^.w);
        q:=f;
        for i:=1 to 4 do begin
                new(p);
                read(p^.w);
                q^.next:=p;
                q:=q^.next
        end;
        q:=nil
end;

var f:pnode;
a:integer;
begin
        tworz(f);
        usun(f);
        while f<>nil do begin
                write(f^.w,' ');
                f:=f^.next
        end;
        readln(a)
end.

