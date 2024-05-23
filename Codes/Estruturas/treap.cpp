struct Treap{
    Treap *lt, *rt;
    int val, sum, lz, sz, pri;
    Treap(int v){
        val = v;
        sum = v;
        pri = rand();
        lz = 0;
        lt = rt = NULL;
        sz = 1;
    }
} *node, *l1, *l2, *l3;

int size(Treap *&treap){
    return treap ? treap->sz : 0;
}

int sm(Treap *&treap){
    return treap ? treap->sum : 0;
}

void upd(Treap *&treap){
    treap->sz = size(treap->lt) + size(treap->rt) + 1;
    treap->sum = sm(treap->lt) + sm(treap->rt)+treap->val;
}

void push(Treap *&treap){
    if(!treap) return;
    if(!treap->lz) return;
    swap(treap->lt, treap->rt);
    treap->lz = 0;
    if(treap->lt) treap->lt->lz ^= 1;
    if(treap->rt) treap->rt->lz ^= 1;
    return;
}

void split(Treap *treap, Treap *&l, Treap *&r, int val){
    push(treap);
    if(!treap){
        l = r = NULL;
        return;
    }
    if(size(treap->lt)+1 <= val){
        split(treap->rt, l, r, val-size(treap->lt)-1);
        treap->rt = l;
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
    push(l);
    push(r);
    if(!l){
        treap = r;
        return;
    }
    if(!r){
        treap = l;
        return;
    }
    if(l-> pri > r-> pri){
        merge(l->rt, l-> rt, r);
        treap = l;
        upd(treap);
        return;
    }
    else{
        merge(r->lt, l, r->lt);
        treap = r;
        upd(treap);
        return;
    }
}

void reverse(Treap *treap){
    treap->lz ^= 1;
    push(treap);
    return;
}

void swp(Treap *&treap, int i, int j){
    split(treap, l1, l2, i-1);
    split(l2, l2, l3, j-i+1);
    reverse(l2);
    merge(treap, l1, l2);
    merge(treap, treap, l3);
    return;
}

void query(Treap *&treap, int i, int j){
    split(treap, l1, l2, i-1);
    split(l2, l2, l3, j-i+1);
    cout << l2->sum << '\n';
    merge(treap, l1, l2);
    merge(treap, treap, l3);
    return;
}

void printt(Treap *&treap){
    if(!treap) return;
    push(treap);
    printt(treap->lt);
    cout << treap->val << ' ';
    printt(treap->rt);
}
