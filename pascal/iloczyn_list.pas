type    pnode=^node;
        node=record
               w:integer;
               next:pnode;
               end;

procedure iloczyn(var f1,f2,f:pnode);
var q,p:pnode;
begin
        f:=nil;
        while (f1<>nil) and (f2<>nil) do begin
                if f1^.w<f2^.w then begin
                        q:=f1;
                        f1:=f1^.next;
                        dispose(q)
                end else if f1^.w>f2^.w then begin
                        q:=f2;
                        f2:=f2^.next;
                        dispose(q)
                end else begin
                        if f<>nil then begin
                                p^.next:=f1;
                                p:=p^.next
                        end else begin
                                f:=f1;
                                p:=f
                        end;
                        q:=f2;
                        f2:=f2^.next;
                        dispose(q);
                        f1:=f1^.next;
                        p^.next:=nil
                end
        end;
        if f1=nil then while f2<>nil do begin
                q:=f2;
                f2:=f2^.next;
                dispose(q)
        end else if f2=nil then begin
                q:=f1;
                f1:=f1^.next;
                dispose(q)
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

var f1,f2,f:pnode;

begin
        tworz(f1);
        tworz(f2);
        iloczyn(f1,f2,f);
        while f<>nil do begin
                write(f^.w);
                f:=f^.next
        end;
        readln
end.

