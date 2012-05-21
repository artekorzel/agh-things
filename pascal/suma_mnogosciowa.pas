type
        pwezel=^wezel;
        wezel=record
                val:integer;
                next:pwezel;
        end;

procedure sumamn(var first1,first2,first:pwezel);
var p,p1,q,q1:pwezel;
begin
        if first1^.val<=first2^.val then begin
                first:=first1;
                first1:=first1^.next;
                dispose(first1);
                p1:=first2;
                dispose(first2);
        end else begin
                first:=first2;
                first2:=first2^.next;
                dispose(first2);
                p1:=first1;
                dispose(first1);
        end;
        q:=first;
        p:=first^.next;
        while((p1<>nil) and (p<>nil)) do begin

                   if ((p1<>nil) and (p<>nil) and (p^.val>p1^.val)) then begin
                          q^.next:=p1;
                          q:=p1;
                          p1:=p1^.next
                   end;
                   if ((p1<>nil) and (p<>nil) and (p^.val=p1^.val)) then begin
                          q:=p1;
                          p1:=p1^.next;
                          q1:=p;
                          p:=p^.next;
                          dispose(q1)
                   end;
                   if ((p1<>nil) and (p<>nil) and (p^.val<p1^.val)) then begin
                          q^.next:=p;
                          q:=p;
                          p:=p^.next
                   end
        end;
        if p1=nil then q^.next:=p
        else q^.next:=p1
end;



