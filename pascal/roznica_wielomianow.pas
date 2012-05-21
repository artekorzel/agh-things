type pnode=^node;
        node=record
                potega,wspolcz:integer;
                next:pnode;
        end;

procedure roznicawiel(f1,f2:pnode; var f:pnode);
var
a,b,c:pnode;
begin
       a:=f1;
       b:=f2;
       if (a<>nil) and (b<>nil) then begin
             new(f);
             f^.potega:=a^.potega;
             f^.wspolcz:=a^.wspolcz-b^.wspolcz;
             a:=a^.next;
             b:=b^.next;
             c:=f;

         while((a<>nil) and (b<>nil)) do begin
             new(c^.next);
             c:=c^.next;
             c^.potega:=a^.potega;
             c^.wspolcz:=a^.wspolcz-b^.wspolcz;
             a:=a^.next;
             b:=b^.next;
         end;
         while ((a=nil) and (b<>nil)) do begin
             new(c^.next);
             c:=c^.next;
             c^.potega:=b^.potega;
             c^.wspolcz:=b^.wspolcz;
             b:=b^.next;
         end;
         while ((b=nil) and (a<>nil)) do begin
             new(c^.next);
             c:=c^.next;
             c^.potega:=a^.potega;
             c^.wspolcz:=a^.wspolcz;
             a:=a^.next;
         end;
         c:=nil;
       end else if (a=nil) and (b=nil) then begin
              new(c); c:=nil;
       end else if a=nil then while (b<>nil) do begin
             new(c);
             c^.potega:=b^.potega;
             c^.wspolcz:=b^.wspolcz;
             b:=b^.next;
             c:=c^.next;
       end else if b=nil then while (a<>nil) do begin
             new(c^.next);
             c:=c^.next;
             c^.potega:=a^.potega;
             c^.wspolcz:=a^.wspolcz;
             a:=a^.next;
       end;
end;