u:=0.65cm;
f:=0.2*u;

def drawDancefloor =
  pair A,B;
  A:=(0,0);
  B:=(10u,0);

  drawarrow A--B;
  drawarrow B--A;

  for i=1 upto 9:
    draw (i*u, -u/10) -- (i*u, 0);
    label (decimal(i), (i*u, -0.35u) );
  endfor;
enddef;

def drawGuy(expr x) =
  path body;
  body := (0, 0) -- (1f, 1f) -- (1f, 3f) -- (1f, 2f) -- (0f, 2f) -- (2f, 2f) -- (1f, 2f) -- (1f, 1f) -- (2f, 0f);
  path head;
  head := fullcircle scaled f shifted (1f, 3.5f);

  draw body shifted (x*u - 1f, 0.3f);
  draw head shifted (x*u - 1f, 0.3f);
enddef;

def drawBaseline(expr width) =
  pair A,B;
  A:=(0,0);
  B:=(width*u,0);

  draw A--B;
  draw B--A;

%  for i=0 upto width - 1:
%    draw (i*u, -u/10) -- (i*u, 0);
%     label (decimal(i + 1), (i*u + 0.5u, -0.35u) );
%  endfor;
enddef;

def drawBar(expr x, height, tint) =
    path bar;
    tinydisplacement := 0.02u;
    bar := (tinydisplacement, 0) -- (tinydisplacement, height*u) -- (u, height*u) -- (u, 0) -- cycle;
    draw bar shifted ((x - 1)*u, 0);
    fill bar shifted ((x - 1)*u, 0) withcolor tint*white;
    
    label (decimal(height), (x*u - 0.5u, -0.35u) );
enddef;


def drawRectangle(expr left, right, top, bottom) =
    path box;
    box := (left*u, bottom*u) -- (right*u, bottom*u) -- (right*u, top*u) -- (left*u, top*u) -- cycle;
    
    picture lines;
    lines :=  image(
        for i = -150 step 8 until 150:
        draw (i,-50) -- (i+200,150) withpen pencircle scaled 0.05u;
        endfor;
        clip currentpicture to box;
    );
    
    draw lines;
    
    draw box shifted (0, 0) withpen pencircle scaled 0.05u;
    % fill box withcolor 1.0white;
enddef;

beginfig(1)

  drawBaseline(6);
  drawBar(1, 2, 0.3);
  drawBar(2, 3, 1.0);
  drawBar(3, 1, 0.7);
  drawBar(4, 7, 1.0);
  drawBar(5, 3, 0.7);
  drawBar(6, 5, 0.3);
  
endfig;

beginfig(2)

  drawBaseline(6);
  drawBar(1, 2, 0.3);
  drawBar(2, 3, 1.0);
  drawBar(3, 1, 0.7);
  drawBar(4, 7, 1.0);
  drawBar(5, 3, 0.7);
  drawBar(6, 5, 0.3);
  
  drawRectangle(0, 6, 1, 0);

endfig;

beginfig(3)

  drawBaseline(6);
  drawBar(1, 2, 0.3);
  drawBar(2, 3, 1.0);
  drawBar(3, 1, 0.7);
  drawBar(4, 7, 1.0);
  drawBar(5, 3, 0.7);
  drawBar(6, 5, 0.3);
  
  drawRectangle(3, 6, 3, 0);
endfig;

beginfig(4)
  drawBaseline(6);
  drawBar(1, 2, 0.3);
  drawBar(2, 3, 1.0);
  drawBar(3, 1, 0.7);
  drawBar(4, 7, 1.0);
  drawBar(5, 3, 0.7);
  drawBar(6, 5, 0.3);
  drawRectangle(0, 3, 2, 0);
endfig;

beginfig(5)
  drawBaseline(6);
  drawBar(1, 2, 0.3);
  drawBar(2, 3, 1.0);
  drawBar(3, 1, 0.7);
  drawBar(4, 7, 1.0);
  drawBar(5, 3, 0.7);
  drawBar(6, 5, 0.3);
  drawRectangle(4, 6, 3, 0);
endfig;

beginfig(6)
  drawBaseline(6);
  drawBar(1, 2, 0.3);
  drawBar(2, 3, 1.0);
  drawBar(3, 1, 0.7);
  drawBar(4, 7, 1.0);
  drawBar(5, 3, 0.7);
  drawBar(6, 5, 0.3);
  drawRectangle(2, 4, 6, 5);
endfig;

beginfig(7) % valid
  drawBaseline(6);
  drawBar(1, 2, 0.3);
  drawBar(2, 3, 1.0);
  drawBar(3, 1, 0.7);
  drawBar(4, 7, 1.0);
  drawBar(5, 3, 0.7);
  drawBar(6, 5, 0.3);
  
  drawRectangle(3.2, 5.8, 2.7, 0.9);
endfig;


beginfig(8) % sample 2 
  drawBaseline(3);
  drawBar(1, 2, 1.0);
  drawBar(2, 2, 1.0);
  drawBar(3, 2, 1.0);
  drawRectangle(0, 3, 2, 0);
%  currentpicture := currentpicture scaled 0.8;
endfig;

beginfig(9) % sample 3
  drawBaseline(5);
  drawBar(1, 3, 0.3);
  drawBar(2, 2, 1.0);
  drawBar(3, 1, 0.3);
  drawBar(4, 2, 1.0);
  drawBar(5, 3, 0.3);
    
  
  drawRectangle(0, 5, 1, 0);
%  currentpicture := currentpicture scaled 0.8;
endfig;

beginfig(10) % sample 4
  drawBaseline(6);
  drawBar(1, 1, 1.0);
  drawBar(2, 2, 0.75);
  drawBar(3, 3, 0.5);
  drawBar(4, 4, 0.25);
  drawBar(5, 5, 0.75);
  drawBar(6, 6, 1.0);

  drawRectangle(2, 6, 3, 0);
%  currentpicture := currentpicture scaled 0.8;
endfig;

beginfig(11) % sample 5
  drawBaseline(7);
  drawBar(1, 1, 1.0);
  drawBar(2, 2, 0.5);
  drawBar(3, 3, 1.0);
  drawBar(4, 4, 0.5);
  drawBar(5, 3, 1.0);
  drawBar(6, 2, 0.5);
  drawBar(7, 1, 1.0);

  drawRectangle(1, 6, 2, 0);
%  currentpicture := currentpicture scaled 0.8;
endfig;

beginfig(12) % sample 6
  drawBaseline(10);
  drawBar(1, 2, 0.5);
  drawBar(2, 1, 1.0);
  drawBar(3, 2, 1.0);
  drawBar(4, 1, 1.0);
  drawBar(5, 1, 0.5);
  drawBar(6, 2, 1.0);
  drawBar(7, 1, 1.0);
  drawBar(8, 2, 0.5);
  drawBar(9, 2, 0.5);
  drawBar(10, 1, 1.0);
   
  drawRectangle(0, 10, 1, 0);
%  currentpicture := currentpicture scaled 0.8;
endfig;


end.
