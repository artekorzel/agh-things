type    pnode=^node;
        node=record
             val:integer;
             r,l:pnode;
             end;
        tab=array of pnode;

procedure wypisz(f:pnode);
begin
        if f<>nil then begin
                write(f^.val);
                wypisz(f^.l);
                wypisz(f^.r)
        end
end;

procedure wypisz2(f:pnode);
var
t:tab;
i:integer;
begin
        setlength(t,1);
        t[0]:=f;
        i:=1;
        repeat
           repeat
           if t[i]<>nil then begin
                setlength(t,i+1);
                write(t[i]^.val);
                if t[i+1]<>t[i]^.l then begin
                        t[i+1]:=t[i]^.l;
                        inc(i)
                end else begin
                        dec(i);
                        if i=1 then break
                end
           end;
           until t[i]=nil;
           dec(i);
           while (i>0) do
             if t[i+1]<>t[i]^.r then begin
                t[i+1]:=t[i]^.r;
                inc(i);
             end else dec(i);
        until (i=0) and (t[1]=t[0]^.r)
end;








