type
        pnode=^node;
        node=record
                val:integer;
                next:pnode;
                end;
        tab_wsk=array[0..9] of pnode;

procedure tworz(var f:pnode);
var p,q:pnode;
i:integer;
begin
        new(f);
        read(f^.val);
        q:=f;
        for i:=1 to 9 do begin
                new(p);
                read(p^.val);
                q^.next:=p;
                q:=q^.next
        end;
        q:=nil
end;

function dzielilacz(var f:pnode):pnode;
var p,q:pnode;
t:tab_wsk;
i:integer;
begin
        for i:=0 to 9 do t[i]:=nil;

        while (f<>nil) do begin
                i:=f^.val mod 10;
                q:=t[i];
                t[i]:=f;
                f:=f^.next;
                t[i]^.next:=q
        end;

        for i:=0 to 8 do begin
                p:=t[i];
                while (p<>nil) do begin
                        q:=p;
                        p:=p^.next
                end;
                if (q<>nil) then q^.next:=t[i+1]
                else t[i]:=t[i+1]
        end;
        dzielilacz:=t[0]
end;

var f:pnode;
i:integer;
begin
        tworz(f);
        f:=dzielilacz(f);
        while (f<>nil) do begin
                write(f^.val,' ');
                f:=f^.next
        end;
        readln(i)
end.




















