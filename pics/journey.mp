u := 1cm;

beginfig(1)
  drawarrow (0, 0)--(1u, 0);
  drawarrow (1u, 0)--(2u, 0);
  drawarrow (2u, 0)--(2u, 1u);
  drawarrow (2u, 1u)--(1u, 1u);
  drawarrow (1u, 1u)--(1u, 0);

  drawarrow (1u, 0)--(2u, 0);
  drawarrow (2u, 0)--(3u, 0);
  drawarrow (3u, 0)--(3u, 1u);
  drawarrow (3u, 1u)--(2u, 1u);
  drawarrow (2u, 1u)--(2u, 0);

  drawarrow (2u, 0)--(3u, 0);
  drawarrow (3u, 0)--(4u, 0);
  drawarrow (4u, 0)--(4u, 1u);
  drawarrow (4u, 1u)--(3u, 1u);
  drawarrow (3u, 1u)--(3u, 0);

  fill fullcircle scaled 3pt;
  label.bot (btex $(0,0)$ etex, (0,0));
endfig;

end.