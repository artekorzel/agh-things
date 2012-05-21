type    pnode=^node;
        node=record
                w:integer;
                next:pnode;
                end;

var
a,b,c:node;
first:pnode;

procedure (var first:pnode);
