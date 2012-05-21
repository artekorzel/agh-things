const n=5;
type    pnode=^node;
        node=record
               w:integer;
               next:pnode;
               end;

procedure klucznik(var f:pnode; var k:integer);
p,q:pnode;
begin
        p:=f;
        q:=nil;
        while (p<>nil) and (p^.w<>k) do begin
                q:=p;
                p:=p^.next
        end;
        if p=nil then begin
                new(p);
                q^.next:=p;
                p^.w:=k
        else begin
                if p=f then f:=f^.next
                else q^.next:=p^.next
                dispose(p)
        end
end;
