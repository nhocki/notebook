class splay {
public:
    splay *sons[2], *up, *path_up;
    splay() : up(NULL), path_up(NULL) {
        sons[0] = sons[1] = NULL;
    }

    bool is_r(splay* n) {
        return n == sons[1];
    }
};

void rotate(splay* t, bool to_l) {
    splay* n = t->sons[to_l];       swap(t->path_up, n->path_up);
    t->sons[to_l] = n->sons[!to_l]; if(t->sons[to_l]) t->sons[to_l]->up = t;
    n->up = t->up;                  if(n->up) n->up->sons[n->up->is_r(t)] = n;
    n->sons[!to_l] = t;             t->up = n;
}

void do_splay(splay* n) {
    for(splay* p; (p = n->up) != NULL; )
        if(p->up == NULL)
            rotate(p, p->is_r(n));
        else {
            bool dirp = p->is_r(n), dirg = p->up->is_r(p);
            if(dirp == dirg)
                rotate(p->up, dirg), rotate(p, dirp);
            else
                rotate(p, dirp), rotate(n->up, dirg);
        }
}

struct link_cut {
    splay* vtxs;
    link_cut(int numv) { vtxs = new splay[numv]; }
    ~link_cut() { delete[] vtxs; }

    void access(splay* ov) {
        for(splay *w = ov, *v = ov; w != NULL; v = w, w = w->path_up) {
            do_splay(w);
            if(w->sons[1]) w->sons[1]->path_up = w, w->sons[1]->up = NULL;
            if(w != v) w->sons[1] = v, v->up = w, v->path_up = NULL;
            else w->sons[1] = NULL;
        }
        do_splay(ov);
    }

    splay* find(int v) {
        splay* s = &vtxs[v];
        access(s); while(s->sons[0]) s = s->sons[0]; do_splay(s);
        return s;
    }

    void link(int parent, int son) {
        access(&vtxs[son]); access(&vtxs[parent]);
        assert(vtxs[son].sons[0] == NULL);
        vtxs[son].sons[0] = &vtxs[parent];
        vtxs[parent].up = &vtxs[son];
    }

    void cut(int v) {
        access(&vtxs[v]);
        if(vtxs[v].sons[0]) vtxs[v].sons[0]->up = NULL;
        vtxs[v].sons[0] = NULL;
    }

    int lca(int v, int w) {
        access(&vtxs[v]); access(&vtxs[w]); do_splay(&vtxs[v]);
        if(vtxs[v].path_up == NULL) return v;
        return vtxs[v].path_up - vtxs;
    }
};
