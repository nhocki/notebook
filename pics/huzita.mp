u := 0.8cm;

beginfig(1)
  draw (0u, 3u)--(6u, 3u);
  draw (3u, 0u)--(3u, 6u);
  dotlabel.rt (btex $p_1$ etex, (5u, 4u));
  dotlabel.top (btex $p_2$ etex, (4u, 5u));
  label.top (btex $l_2$ etex, (6u, 3u));
  label.rt (btex $l_1$ etex, (3u, 6u));
  draw (1u, 6u)--(6u, 1u) dashed evenly;
  drawarrow (5u, 4u)--(3u, 2u);
  drawarrow (4u, 5u)--(2u, 3u);
endfig;

end.
