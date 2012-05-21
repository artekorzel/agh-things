type pnode=^node;
        node=record
                val:integer;
                next:pnode;
                end;

procedure tworz(var f:pnode);
var p,q:pnode;
i:integer;
begin
        new(f);
        read(f^.val);
        q:=f;
        for i:=1 to 4 do begin
                new(p);
                read(p^.val);
                q^.next:=p;
                q:=q^.next
        end;
        q:=nil
end;

procedure scal(var f1,f2:pnode);
var tmp,p,q:pnode;
begin
        new(p); p^.next:=f1; f1:=p;
        while (f2<>nil) do begin
                q:=f1;
                p:=q^.next;
                while (p<>nil) and (p^.val<f2^.val) do begin
                        q:=p;
                        p:=p^.next
                end;
                if (p<>nil) then begin
                        if (p^.val>f2^.val) then begin
                                q^.next:=f2;
                                q:=f2;
                                f2:=f2^.next;
                                q^.next:=p
                        end else begin
                                tmp:=f2;
                                f2:=f2^.next;
                                dispose(tmp)
                        end
                end else begin
                   if (q<>f1) and (q^.val<f2^.val) then begin
                        q^.next:=f2;
                        q:=f2;
                        f2:=f2^.next;
                        q^.next:=p
                   end else if (q=f1) then begin
                        q^.next:=f2;
                        f2:=f2^.next;
                        q:=f2;
                        q^.next:=nil
                   end
                end
        end;
        p:=f1;
        f1:=f1^.next;
        dispose(p)
end;

var f1,f2:pnode;
begin
        tworz(f1);
        tworz(f2);
        scal(f1,f2);
        while(f1<>nil) do begin
                write(f1^.val,' ');
                f1:=f1^.next
        end;
        readln()
end.















