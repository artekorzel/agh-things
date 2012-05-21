type
        pwezel=^wezel;
        wezel=record
                val:integer;
                next:pwezel;
        end;

procedure sumamn(var f1,f2,first:pwezel);
var p,q:pwezel;
begin
        if f1^.val<=f2^.val then begin
                first:=f1;
                f1:=f1^.next;
                if f1^.val=f2^.val then begin
                        q:=f2;
                        f2:=f2^.next;
                        dispose(q)
                end
        end else begin
                first:=f2;
                f2:=f2^.next;
        end;
        p:=first;
        while((f1<>nil) and (f2<>nil)) do begin
                if (f1^.val<=f2^.val) then begin
                        p^.next:=f1;
                        p:=f1;
                        f1:=f1^.next;
                        if f1^.val=f2^.val then begin
                                q:=f2;
                                f2:=f2^.next;
                                dispose(q)
                        end
                end else begin
                        p^.next:=f2;
                        p:=f2;
                        f2:=f2^.next
                end
        end;
        if f1=nil then p^.next:=f2
        else p^.next:=f1
end;