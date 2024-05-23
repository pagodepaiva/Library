struct Treap{
    Treap *lt, *rt;
    char val;
    int sz, pri;
    Treap(char v){
        val = v;
        sz = 1;
        pri = rand();
        lt = rt = NULL;
    }
} *node, *l1, *l2, *r1;

int size(Treap *treap){
    return (treap ? treap -> sz : 0);
}

void upd(Treap *treap){
    treap -> sz = size(treap->lt)+size(treap->rt)+1;
}

void split(Treap *treap, Treap *&l, Treap *&r, int val){
    if(treap == NULL){
        l = r = NULL;
        return;
    }
    if(size(treap->lt)+1 <= val){
        split(treap->rt, l, r, val-size(treap->lt)-1);
         treap -> rt = l;
         upd(treap);
         l = treap;
         return;
    }
    else{
        split(treap->lt, l, r, val);
        treap->lt = r;
        upd(treap);
        r = treap;
        return;
    }
}

void merge(Treap *&treap, Treap *l, Treap *r){
    if(!l){
        treap = r;
        return;
    }
    if(!r){
        treap = l;
        return;
    }
    if(l->pri > r->pri){
        merge(r->lt, l, r-> lt);
        treap = r;
        upd(treap);
        return;
    }
    else{
        merge(l->rt, l->rt, r);
        treap = l;
        upd(treap);
        return;
    }
}
