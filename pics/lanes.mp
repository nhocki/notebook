
w := 12cm;
h := 8mm;
e := .5pt;
a := 5cm;
b := 7cm;

path c;

c := (-3.5mm,-2mm){left}..{up}(-4mm,-1.5mm)--
     (-4mm,1.5mm){up}..{right}(-3.5mm,2mm)--
     (3.5mm,2mm){right}..{down}(4mm,1.5mm)--
     (4mm,-1.5mm){down}..{left}(3.5mm,-2mm)--cycle;

path d;

q := 0.3mm;
r := 1.2mm;

d := (-3.5mm+r,-2mm+q){left}..{up}(-4mm+r,-1.5mm+q)--
     (-4mm+r,1.5mm-q){up}..{right}(-3.5mm+r,2mm-q)--
     (3.5mm-r,2mm-q){right}..{down}(4mm-r,1.5mm-q)--
     (4mm-r,-1.5mm+q){down}..{left}(3.5mm-r,-2mm+q)--cycle;

def car(expr p, k) =
  draw c shifted p;
  draw d shifted p shifted (-.7mm * k,0);
enddef;

beginfig(1)
  draw (0, 0)--(w,  0);
  draw (0, h)--(w,  h) dashed evenly;
  draw (0,2h-e)--(w, 2h-e) dashed evenly;
  draw (0,2h+e)--(w, 2h+e) dashed evenly;
  draw (0,3h-e)--(w, 3h-e) dashed evenly;
  draw (0,3h+e)--(w, 3h+e) dashed evenly;
  draw (0,4h)--(w, 4h) dashed evenly;
  draw (0,5h)--(w, 5h);

  drawarrow (a, 0.5h)--(b, 0.5h);
  drawarrow (a, 1.5h)--(b, 1.5h);
  drawarrow (a, 2.5h)--(b, 2.5h);
  drawarrow (b, 2.5h)--(a, 2.5h);
  drawarrow (b, 3.5h)--(a, 3.5h);
  drawarrow (b, 4.5h)--(a, 4.5h);

  car((3cm,0.5h), 1);
  car((1cm,1.5h), 1);
  car((9cm,3.5h), -1);

endfig;

end;