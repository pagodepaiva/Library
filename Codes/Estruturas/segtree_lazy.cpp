struct Segtree{
    int tree[4*N], lazyadd[4*N], lazyset[4*N];
    int join(int a, int b){
        return a+b;
    }
    void unlazy(int node, int l, int r){
        if(lazyset[node] != 0){
            tree[node] = (r-l+1)*lazyset[node];
            if(l != r){
                lazyadd[2*node] = lazyadd[2*node+1] = 0;
                lazyset[2*node] = lazyset[2*node+1] = lazyset[node];
            }
            lazyset[node] = 0;
        }
        if(lazyadd[node] != 0){
            tree[node] += (r-l+1)*lazyadd[node];
            if(l != r){
                lazyadd[2*node] += lazyadd[node];
                lazyadd[2*node+1] += lazyadd[node];
            }
            lazyadd[node] = 0;
        }
    }
    void updateset(int node, int l, int r, int tl, int tr, int val){
        unlazy(node, tl, tr);
        if(l > tr or tl > r)
            return;
        if(l <= tl and tr <= r){
            lazyset[node] = val;
            lazyadd[node] = 0;
            unlazy(node, tl, tr);
            return;
        }
        int mid = (tl+tr)/2;
        updateset(2*node, l, r, tl, mid, val);
        updateset(2*node+1, l, r, mid+1, tr, val);
        tree[node] = join(tree[2*node], tree[2*node+1]);
        return;
    }
    void updateadd(int node, int l, int r, int tl, int tr, int val){
        unlazy(node, tl, tr);
        if(l > tr or tl > r)
            return;
        if(l <= tl and tr <= r){
            lazyadd[node] += val;
            unlazy(node, tl, tr);
            return;
        }
        int mid = (tl+tr)/2;
        updateadd(2*node, l, r, tl, mid, val);
        updateadd(2*node+1, l, r, mid+1, tr, val);
        tree[node] = join(tree[2*node], tree[2*node+1]);
        return;
    }
    int query(int node, int l, int r, int tl, int tr){
        unlazy(node, tl, tr);
        if(l > tr or tl > r)
            return 0;
        if(l <= tl and tr <= r)
            return tree[node];
        int mid = (tl+tr)/2;
        return join(query(2*node, l, r, tl, mid), query(2*node+1, l, r, mid+1, tr));
    }
} seg;
