type    pnode=^node;
        node=record
               w:integer;
               next:pnode;
               end;

procedure polacz(var f,f1:pnode);
var p,q,tmp:pnode;
begin
        while f1<>nil do begin
                p:=f;
                q:=p^.next;
                if q=nil then begin
                        while (q=nil) and (f1<>nil) do begin
                                if p^.w<f1^.w then begin
                                        p^.next:=f1;
                                        f1:=f1^.next;
                                        q:=p^.next;
                                        q^.next:=nil
                                end else if p^.w>f1^.w then begin
                                        f:=f1;
                                        f1:=f1^.next;
                                        f^.next:=p;
                                        q:=p;
                                        p:=f
                                end else begin
                                        tmp:=f1;
                                        f1:=f1^.next;
                                        dispose(tmp)
                                end
                        end
                end else begin
                        if (q<>nil) then begin
                                if q^.w<f1^.w then begin
                                        p:=q;
                                        q:=q^.next
                                end else if q^.w>f1^.w then begin
                                   if f1^.w<>p^.w then begin
                                        p^.next:=f1;
                                        tmp:=f1;
                                        f1:=f1^.next;
                                        tmp^.next:=q
                                   end else begin
                                        tmp:=f1;
                                        f1:=f1^.next;
                                        dispose(tmp)
                                   end
                                end else begin
                                        tmp:=f1;
                                        f1:=f1^.next;
                                        dispose(tmp)
                                end
                        end
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

var f,f1:pnode;

begin
        tworz(f);
        tworz(f1);
        polacz(f,f1);
        while f<>nil do begin
                write(f^.w,' ');
                f:=f^.next
        end;
        readln
end.




