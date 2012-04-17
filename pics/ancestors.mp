input boxes

vardef cuta(suffix a,b) expr p =
draw p cutbefore bpath.a cutafter bpath.b;
point .5*length p of p
enddef;

beginfig(1);
verbatimtex \def\stk#1#2{$\displaystyle{\matrix{#1\cr#2\cr}}$} etex
circleit.aa(btex\stk A{6} etex);
circleit.bb(btex \stk B{3} etex);
circleit.cc(btex \stk C{4} etex);
circleit.dd(btex \stk D{-1} etex);
circleit.ee(btex \stk E{1} etex);
circleit.ff(btex \stk F{-5} etex);
circleit.gg(btex \stk G{1} etex);

u := 3cm;
aa.c - bb.c = (0.75u, 0.75u);
bb.c - cc.c = (0.5u, 0.75u);
bb.c - dd.c = (-0.5u, 0.75u);

aa.c - ee.c = (0.0u, 0.75u);

aa.c - ff.c = (-0.75u, 0.75u);

ff.c - gg.c = (0.2u, 0.75u);

drawboxed(aa,bb,cc,dd,ee,ff,gg);

label.ulft(btex$ $etex, cuta(aa,bb) aa.c{dir200}..bb.c);
label.ulft(btex$ $etex, cuta(aa,ee) aa.c{dir-90}..ee.c);
label.ulft(btex$ $etex, cuta(aa,ff) aa.c{dir-20}..ff.c);

label.ulft(btex$ $etex, cuta(bb,cc) bb.c{dir210}..cc.c);
label.ulft(btex$ $etex, cuta(bb,dd) bb.c{dir-20}..dd.c);

label.ulft(btex$ $etex, cuta(ff,gg) ff.c{dir-90}..gg.c);

endfig;

end.