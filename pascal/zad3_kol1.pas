type pnode=^node;
        node=record
                val:integer;
                next:pnode;
                end;

procedure tworz(var f:pnode);
var p,q:pnode;
i:integer;
begin
        new(f);
        read(f^.val);
        q:=f;
        for i:=1 to 7 do begin
                new(p);
                read(p^.val);
                q^.next:=p;
                q:=q^.next
        end;
        q:=nil
end;

procedure usun(var f:pnode);
var
 r,tmp,pocz:pnode;
 ilosc:integer;

        function znajdz(f:pnode; var pocz:pnode; var ilosc:integer):boolean;
        var p,q,apocz:pnode; zly,k:integer;
        begin
                zly:=0;
                q:=f;
                p:=f^.next;
                while (p<>nil) do begin
                        k:=0;
                        apocz:=q;
                        q:=p;
                        p:=p^.next;
                        while(p<>nil) and (p^.val>q^.val) do begin
                                inc(k);
                                q:=p;
                                p:=p^.next
                        end;

                        if (ilosc<k) and (zly<k) then begin
                                ilosc:=k;
                                pocz:=apocz;
                                znajdz:=true
                        end else if (ilosc=k) then begin
                                zly:=ilosc;
                                ilosc:=0;
                                znajdz:=false
                        end
                end
        end;
begin
        new(pocz);
        pocz^.next:=f;
        f:=pocz;
        pocz:=nil;
        ilosc:=0;
        if znajdz(f,pocz,ilosc) then begin
                r:=pocz^.next;
                pocz^.next:=nil;
                while (ilosc>=0) do begin
                        tmp:=r;
                        r:=r^.next;
                        dispose(tmp);
                        dec(ilosc)
                end;
                pocz^.next:=r
        end;
        tmp:=f;
        f:=f^.next;
        dispose(tmp)
end;

var f:pnode;
    a:integer;
begin
        tworz(f);
        usun(f);
        while f<>nil do begin
                write(f^.val, ' ');
                f:=f^.next
        end;
        writeln;
        readln(a)
end.



























