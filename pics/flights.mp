u := 1mm;
v := 3mm;

vardef sqr(expr x) = x * x enddef;

vardef P(expr x) = (-0.025 sqr(x) + 1.5x - 12.5) enddef;
vardef Q(expr x) = (-0.300 sqr(x) + 18x - 240) enddef;

def flight(expr i, a, b, c) =
  draw (a*u, c*u)--(b*u, c*u) dashed evenly;
  draw (a*u, 0)--(a*u, c*u+v);
  draw (b*u, 0)--(b*u, c*u+v);
  label.top(decimal(i), (.5(a+b)*u, c*u));
enddef;

beginfig(1)
  draw (-10u,0)--(110u,0);

  draw (10u,0) for x=11 upto 50 : --(x*u,P(x)*u) endfor withpen pencircle scaled 1.5pt;
  draw (20u,0) for x=21 upto 40 : --(x*u,Q(x)*u) endfor withpen pencircle scaled 1.5pt;

  for i=0 upto 10 :
    fill fullcircle scaled 3pt shifted (10i * u, 0);
    label.bot(decimal(10i), (10i * u, 0));
  endfor;

  flight(1,  0,  11,  0.975);
  flight(2, 20,  25, 22.500);
  flight(3, 25,  35, 30.000);
  flight(4, 45, 100,  4.375);

endfig;

end.