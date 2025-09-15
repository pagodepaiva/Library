struct Segtree{
    int tree[4*N];
    int join(int a, int b){
        return max(a, b);
    }
    void build(int node, int l, int r){
        if(l == r){
            tree[node] = v[l];
            return;
        }
        int mid = (l+r)/2;
        build(2*node, l, mid);
        build(2*node+1., mid+1, r);
        tree[node] = join(tree[2*node], tree[2*node+1]);
        return;
    }
    void update(int node, int l, int r, int pos, int val){
        if(l == r){
            tree[node] = val;
            return;
        }
        int mid = (l+r)/2;
        if(pos <= mid) update(2*node, l, mid, pos, val);
        else update(2*node+1, mid+1, r, pos, val);
        tree[node] = join(tree[2*node], tree[2*node+1]);
        return;
    }
    int query(int node, int l, int r, int tl, int tr){
        if(l <= tl and tr <= r) return tree[node];
        if(l > tr or tl > r) return 0;
        int mid = (tl+tr)/2;
        return join(query(2*node, l, r, tl, mid), query(2*node+1, l, r, mid+1, tr));
    }
    int busca_esquerda(int node, int l, int r, int tl, int tr, int x){
        if(l > tr or tl > r)
            return -1;
        if(l <= tl and tr <= r){
            int mid = (tl+tr)/2;
            if(tree[node] < x)
                return -1;
            if(tl == tr)
                return tl;
            if(tree[2*node+1] >= x){
                return busca_esquerda(2*node+1, l, r, mid+1, tr, x);
            }
            return busca_esquerda(2*node, l, r, tl, mid, x);
        }
        int mid = (tl+tr)/2;
        int t = busca_esquerda(2*node+1, l, r, mid+1, tr, x);
        if(t != -1)
            return t;
        return busca_esquerda(2*node, l, r, tl, mid, x);
    }
    int busca_direita(int node, int l, int r, int tl, int tr, int x){
        if(l > tr or tl > r)
            return -1;
        if(l <= tl and tr <= r){
            int mid = (tl+tr)/2;
            if(tree[node] < x)
                return -1;
            if(tl == tr)
                return tl;
            if(tree[2*node] >= x){
                return busca_direita(2*node, l, r, tl, mid, x);
            }
            return busca_direita(2*node+1, l, r, mid+1, tr, x);
        }
        int mid = (tl+tr)/2;
        int t = busca_direita(2*node, l, r, tl, mid, x);
        if(t != -1)
            return t;
        return busca_direita(2*node+1, l, r, mid+1, tr, x);
    }
} seg, ans;
