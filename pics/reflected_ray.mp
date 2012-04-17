u := 1cm;

beginfig(1)
    draw (-1u,0) .. (0u,1u) .. (1u,0);
    
    pair normal, incidence;
    normal := (0u, 2u);
    incidence := (0u, 1u);
    drawarrow incidence--normal;

    pair left, right;
    
    left := (-1.5u, 1.4u);
    right := (+1.5u, 1.4u);
    
    drawarrow left--incidence;
    drawarrow incidence--right;
    
    label.top(btex $\vec n$ etex, normal);
    label.top(btex $\vec a$ etex, 1/2[left,incidence]);
    label.top(btex $\vec b$ etex, 1/2[incidence, right]);
endfig;

end.