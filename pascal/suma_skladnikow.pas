type pnode=^node;
        node=record
                val:integer;
                next:pnode;
                end;

procedure ala(first:pnode);
var
p,q,pocz,kon,apocz:pnode;
i,k:integer;
begin
        p:=first;
        q:=first;
        k:=0;
        i:=0;
        apocz:=first;
        while p<>nil do begin
                q:=p;
                p:=p^.next;
                if p^.val>q^.val then inc(k)
                else begin
                        k:=0;
                        apocz:=q;
                end;
                if k>i then begin
                        i:=k;
                        pocz:=apocz;
                        kon:=p
                end;
        end;
        if k<>0 then begin
                p:=pocz^.next;
                pocz^.next:=kon^.next;
                while p<>pocz^.next do begin
                        q:=p;
                        p:=p^.next;
                        dispose(q);
                end;
                if pocz=first then begin
                        first:=pocz^.next;
                        dispose(pocz)
                end;
        end
end;
