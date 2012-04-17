u := 0.8cm;

beginfig(1)
    pair a, b;
    a := (-2u,2u);
    b := (3u,-1u);
    drawdblarrow a .. b;
    
    pair here; here := (-1u, -0.3u);
    pair there; there := (0.5u, 2.2u);
    
    pair hit; hit := (-0.25u, 0.95u);
    
    dotlabel.llft(btex $p$ etex, here);
    dotlabel.urt(btex $q$ etex, there);
    
    dotlabel.llft(btex $a$ etex, a - 0.1 * (a - b));
    dotlabel.urt(btex $b$ etex, b - 0.1 * (b - a));
    
    
    draw hit withpen pencircle scaled 3bp;
    
    label.rt(btex $v$ etex, hit + (0.1u, 0.05u));
    
    draw here--there dashed evenly;
    
endfig;

end.