int lf[N], rf[N];

struct Segtree{
    pair <int, int> tree[4*N];
    pair <int, int> join(pair <int, int> a, pair <int, int> b){
        if(a.fr < b.fr) return a;
        if(a.fr > b.fr) return b;
        return a;
    }
    void build(int node, int l, int r){
        if(l == r){
            tree[node] = {b[l], l};
            return;
        }
        int mid = (l+r)/2;
        build(2*node, l, mid);
        build(2*node+1, mid+1, r);
        tree[node] = join(tree[2*node], tree[2*node+1]);
        return;
    }
    pair <int, int> query(int node, int l, int r, int tl, int tr){
        if(l > tr or tl > r) return {1e18+1, 0};
        if(l <= tl and tr <= r) return tree[node];
        int mid = (tl+tr)/2;
        return join(query(2*node, l, r, tl, mid), query(2*node+1, l, r, mid+1, tr));
    }
} seg;
 
int build(int l, int r){
    if(l == r)
        return l;
    if(l > r)
        return -1;
    int pos = seg.query(1, l, r, 1, n).second;
    lf[pos] = build(l, pos-1);
    rf[pos] = build(pos+1, r);
    return pos;
}
