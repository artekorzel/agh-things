program tablice;
uses crt;
const max1=30;
      max2=40;
      zbior = ['w','s','a','d'];

var i,j,k:integer;
    x,y,gwiazd_x,gwiazd_y,numer:integer; {wspolrzedne}
    dlugosc,licznik_drogi,zjedzone:integer; {statystyki}
    ilosc,start_dlug,tempo:integer; {parametry pocztakowe}
    blad,sciany,xy:Boolean; {parametry pocztakowe}
    litera,znak:char;
    tab:array[1..max1,1..max2] of char;
    waz:array['x'..'y',0..max1*max2]of integer; {troche mi sie pomylilo i iksy sa w dol a igreki w bok, ale to nic}

procedure przesun(); {przesuwanie glowy i zeby mozna bylo pozniej usunac dupe}
begin
     tab[waz['x',0],waz['y',0]]:=znak;
     gotoXY(waz['y',0],waz['x',0]);
     write(znak);
     tab[x,y]:=znak;
     gotoXY(y,x);
     write(znak);
     for numer:=dlugosc downto 1 do begin
         waz['x',numer]:=waz['x',numer-1];
         waz['y',numer]:=waz['y',numer-1];
     end;
     waz['x',0]:=x;
     waz['y',0]:=y;
end;
procedure losuj();
begin
     randomize;
     repeat
          gwiazd_x:=random(max1-2)+2;
          gwiazd_y:=random(max2-2)+2;
          if (xy) and (dlugosc>5) then tab[gwiazd_x,gwiazd_y]:=' ';
     until (tab[gwiazd_x,gwiazd_y]=' ');
     tab[gwiazd_x,gwiazd_y]:='*';
     gotoXY(gwiazd_y,gwiazd_x);
     write('*')
end;
procedure wypisz();
begin
     for i:=1 to max1 do begin
          for j:=1 to max2 do
              write(tab[i,j]);
          writeln;
     end;
     writeln('Droga: ',licznik_drogi,'     Dlugosc: ', dlugosc,'     Zjedzone: ', zjedzone);
end;
begin
     {poczatek - pole gry}
     for i:=2 to max1-1 do
         for j:=2 to max2-1 do
             tab[i,j]:=' ';
     for i:=1 to max1 do begin
         tab[i,1]:='|';
         tab[i,max2]:='|';
     end;
     for i:=1 to max2 do begin
         tab[1,i]:='-';
         tab[max1,i]:='-';
     end;
     sciany:=false;
     xy:=false;
     writeln('Sterowanie w s a d.');
     write('Gramy ze scianami czy bez? Sciany - wpisz "s": ');
     readln(litera);
     if litera='s' then sciany:=true
     else if litera='\' then xy:=true;
     write('Podaj tempo gry: ');
     readln(tempo);
     {koniec - pole gry}
     {poczatek - zerowanie weza}
     for i:=0 to max1*max2 do waz['x',i]:=0;
     for i:=0 to max1*max2 do waz['y',i]:=0;
     x:=(max1-2) div 2 +1;
     y:=(max2-2) div 2 +1;
     znak:='X';
     tab[x,y]:=znak;
     dlugosc:=1;
     zjedzone:=0;
     licznik_drogi:=0;
     waz['x',0]:=x;
     waz['y',0]:=y;
     blad:=false;
     repeat
           write('Podaj poczatkowa dlugosc weza: ');
           readln(start_dlug);
     until (start_dlug<(max1-2)*(max2-2)) and (start_dlug>=3);
     {koniec - zerowanie weza}
     {poczatek - losowanie tego co waz zjada}
     repeat
           write('Podaj ile ma byc gwiazdek na planszy: ');
           readln(ilosc);
     until (ilosc<(max1-2)*(max2-2)) and (ilosc>=1);
     for i:=1 to ilosc do losuj();
     {koniec - losowanie tego co waz zjada}
     clrscr;
     wypisz();
     litera := readkey;
     while not blad do begin
        repeat
           {poczatek - zmiana kierunku}
           case litera of
                'w': begin dec(x); znak:='A'; end;
                's': begin inc(x); znak:='V'; end;
                'a': begin dec(y); znak:='<'; end;
                'd': begin inc(y); znak:='>'; end;
                else blad:=true;
           end;
           {koniec - zmiana kierunku}
           {poczatek - uderzenie w sciane, ugryzienie sie w tylek}
           if (not xy) and (sciany) then begin
              if ((tab[x,y]<>' ') and (tab[x,y]<>'*')) or (x <= 1) or (y <= 1) or (x >= max1) or (y >= max2) then begin
                 blad:=true;
                 writeln('zonk');
              end
           end else begin
              {przejscie na druga strone}
              if  x = 1 then x:=max1-1
              else if  y = 1 then y:=max2-1
              else if  x = max1 then x:=2
              else if  y = max2 then y:=2;
              if (not xy) and (tab[x,y]<>' ') and (tab[x,y]<>'*') then begin
                 blad:=true;
                 writeln('zonk');
              end
           end;
           {koniec - uderzenie w sciane, ugryzienie sie w tylek}
           {poczatek - jak tylek caly to jedziemy dalej}
           if not blad then begin
              inc(licznik_drogi);
              {zjadamy}
              if tab[x,y]='*' then begin
                 if dlugosc + ilosc < (max1-2)*(max2-2) then
                    losuj();
                 inc(dlugosc);
                 inc(zjedzone);
                 przesun();
              {nie zjadamy, ale dlugosc startowa nie osiagnieta}
              end else if dlugosc - zjedzone < start_dlug then begin
                 inc(dlugosc);
                 przesun();
              {idziemy dalej}
              end else begin
                 if xy then losuj();
                 przesun();
                 tab[waz['x',dlugosc],waz['y',dlugosc]]:=' ';
                 gotoXY(waz['y',dlugosc],waz['x',dlugosc]);
                 write(' ');
              end;
           end;
           {koniec - jak tylek caly to jedziemy dalej}
           //clrscr;
           //wypisz();
           if (xy) and (dlugosc=max1*max2) then blad:=true;
           gotoXY(1,max1+1);
           writeln('Droga: ',licznik_drogi,'     Dlugosc: ', dlugosc,'     Zjedzone: ', zjedzone);
           if blad then begin
              tab[waz['x',0],waz['y',0]]:=znak;
              {znaczki:) }
              for k:=1 to 10 do begin
                  if (waz['x',0]-k>1) and (waz['y',0]-k>1) then begin gotoXY(waz['y',0]-k,waz['x',0]-k); write('\'); end;
                  if (waz['x',0]+k<max1) and (waz['y',0]-k>1) then begin gotoXY(waz['y',0]-k,waz['x',0]+k); write('/'); end;
                  if (waz['x',0]-k>1) and (waz['y',0]+k<max2) then begin gotoXY(waz['y',0]+k,waz['x',0]-k); write('/'); end;
                  if (waz['x',0]+k<max1) and (waz['y',0]+k<max2) then begin gotoXY(waz['y',0]+k,waz['x',0]+k); write('\'); end;
                  if waz['x',0]-k>1 then begin gotoXY(waz['y',0],waz['x',0]-k); write('|'); end;
                  if waz['x',0]+k<max1 then begin gotoXY(waz['y',0],waz['x',0]+k); write('|'); end;
                  if waz['y',0]-k>1 then begin gotoXY(waz['y',0]-k,waz['x',0]); write('-'); end;
                  if waz['y',0]+k<max2 then begin gotoXY(waz['y',0]+k,waz['x',0]); write('-'); end;
                  delay(40);
              end;
              writeln('Ostateczny wynik: ',(zjedzone div ilosc)*100 div(1+tempo div 10));
           end;
           delay(tempo);
        until (blad) or (keypressed) or (not (litera in zbior));
        litera := readkey;
     end;
     readln;
end.
