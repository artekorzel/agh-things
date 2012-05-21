type    pnode=^node;
        node=record
                w:integer;
                next:pnode;
                end;

procedure odwroc(var first:pnode);
var a,b:pnode;
begin
        if first<>nil then begin
                a:=first;
                first:=first^.next;
                a^.next:=nil;
        end;
        while (first<>nil) do begin
                b:=first;
                first:=first^.next;
                b^.next:=a;
                a:=b;
        end;
        first:=b;
end;
