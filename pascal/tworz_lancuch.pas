type    pnode=^node;
        node=record
               w:integer;
               next:pnode;
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
        end
end;