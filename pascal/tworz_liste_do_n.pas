const n=5;
type    pnode=^node;
        node=record
               w:integer;
               next:pnode;
               end;
var f:pnode;

function tworz(k:integer):pnode;
begin
        if k=n+1 then tworz:=nil
        else begin
                new(tworz);
                tworz^.w:=k;
                tworz^.next:=tworz(k+1)
        end
end;

procedure odwroc(var f:pnode);
var p,q:pnode;
begin
        p:=f;
        q:=nil;
        while p<>nil do begin
                p:=p^.next;
                f^.next:=q;
                q:=f;
                f:=p;

        end;
        f:=q
end;

begin
        f:=tworz(1);
        odwroc(f);
        while f<>nil do begin
                write(f^.w);
                f:=f^.next
        end;
        readln
end.