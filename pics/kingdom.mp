u := 2cm;

beginfig(1)
  z1 = (0u, 1u);
  z2 = (0u, 0u);
  z3 = (1u, 0u);
  z4 = (1u, 1u);
  z5 = (2u, 0u);

  for i=1 upto 5: 
    fill fullcircle scaled 3pt shifted z[i];
  endfor

  label.ulft("1", z1);
  label.llft("2", z2);
  label.bot ("3", z3);
  label.top ("4", z4);
  label.lrt ("5", z5);

  draw z1--z2;
  draw z2--z3;
  draw z3--z4;
  draw z3--z5;

  draw z1--z4 dashed evenly;
  draw z4--z5 dashed evenly;
endfig;

end.
