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
        end;
        q:=nil
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

procedure mnoz(var f1,f2:pnode; var wynik:pnode);
var
        p,q,f1p,f2p,s:pnode;
        tmp:integer;
begin
        odwroc(f1);
        odwroc(f2);
                new(wynik);
                wynik^.w:=0;
                wynik^.next:=nil;
                f2p:=f2;
                s:=wynik;
                while f2p<>nil do begin
                   f1p:=f1;
                   tmp:=0;
                   p:=s;
                   while f1p<>nil do begin
                        if p^.next=nil then begin
                                new(q);
                                p^.next:=q;
                                q^.next:=nil;
                                q^.w:=0;
                        end else q:=p^.next;
                        tmp:=tmp + q^.w + f1p^.w*f2p^.w;
                        q^.w:=tmp mod 10;
                        tmp:=tmp div 10;
                        f1p:=f1p^.next;
                        p:=q;
                   end;
                   if tmp<>0 then begin
                        new(q);
                        p^.next:=q;
                        q^.w:=tmp;
                        q^.next:=nil
                   end;
                   f2p:=f2p^.next;
                   s:=s^.next
                end;
                p:=wynik;
                wynik:=wynik^.next;
                dispose(p);
                odwroc(wynik);
                q:=wynik;
                while (q<>nil) and (q^.w=0) do q:=q^.next;
                while q<>nil do begin
                        write(q^.w);
                        q:=q^.next
                end
end;
var f1,f2,wynik:pnode;
a:integer;

begin
        tworz(f1);
        tworz(f2);
        mnoz(f1,f2,wynik);
        readln(a);
end.





















