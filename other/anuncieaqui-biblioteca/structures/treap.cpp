typedef int TYPE;

class treap {
public:
    treap *left, *right;
    int priority, sons;
    TYPE value;

    treap(TYPE value) : left(NULL), right(NULL), value(value), sons(0) {
        priority = rand();
    }

    ~treap() {
        if(left) delete left;
        if(right) delete right;
    }
};

treap* find(treap* t, TYPE val) {
    if(!t) return NULL;
    if(val == t->value) return t;

    if(val < t->value) return find(t->left, val);
    if(val > t->value) return find(t->right, val);
}

void rotate_to_right(treap* &t) {
    treap* n = t->left;
    t->left = n->right;
    n->right = t;
    t = n;
}

void rotate_to_left(treap* &t) {
    treap* n = t->right;
    t->right = n->left;
    n->left = t;
    t = n;
}

void fix_augment(treap* t) {
    if(!t) return;
    t->sons = (t->left ? t->left->sons + 1 : 0) +
        (t->right ? t->right->sons + 1 : 0);
}

void insert(treap* &t, TYPE val) {
    if(!t)
        t = new treap(val);
    else
        insert(val <= t->value ? t->left : t->right, val);

    if(t->left && t->left->priority > t->priority)
        rotate_to_right(t);
    else if(t->right && t->right->priority > t->priority)
        rotate_to_left(t);

    fix_augment(t->left); fix_augment(t->right); fix_augment(t);
}

inline int p(treap* t) {
    return t ? t->priority : -1;
}

void erase(treap* &t, TYPE val) {
    if(!t) return;

    if(t->value != val)
        erase(val < t->value ? t->left : t->right, val);
    else {
        if(!t->left && !t->right)
            delete t, t = NULL;
        else {
            p(t->left) < p(t->right) ? rotate_to_left(t) : rotate_to_right(t);
            erase(t, val);
        }
    }

    fix_augment(t->left); fix_augment(t->right); fix_augment(t);
}

