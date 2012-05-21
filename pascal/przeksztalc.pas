var
a,b,n:integer;

function przeksztalc(a,b,n:integer):boolean;
var bool:boolean;

        procedure ala(akta,k:integer; var bool:boolean);

        begin
                if k=0 then begin
                        if akta=b then begin
                                bool:=true
                        end
                end else
                  if akta=b then ala(akta,0,bool)
                  else begin
                        ala(akta+1,k-1,bool);
                        ala(akta*3,k-1,bool);
                        if akta mod 2 = 0 then ala(akta div 2,k-1,bool)
                  end
        end;
begin
        bool:=false;
        ala(a,n,bool);
        przeksztalc:=bool
end;

begin
        readln(a,b,n);
        if przeksztalc(a,b,n) then write('TAK') else write('NIE');
        readln;
end.
