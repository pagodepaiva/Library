//
const int N = ;
//

struct Segtree{
    int tree[4*N], lazy[4*N];
 
    int join(int a, int b){
        return a+b;
    }
 
    void unlazy(int node, int l, int r){
        tree[node] += lazy[node]*(r-l+1);
        if(l < r){
            lazy[2*node] += lazy[node];
            lazy[2*node+1] += lazy[node];
        }
 
        lazy[node] = 0;
    }
 
    int build(int node, int l, int r){
        if(l == r){
            tree[node] = 0;
            lazy[node] = 0;
            return 0;
        }
 
        int mid = (l+r)/2;
 
        build(2*node, l, mid);
        build(2*node+1, mid+1, r);
 
        tree[node] = 0;
        lazy[node] = 0;
        return 0;
    }
 
    void update(int node, int l, int r, int val, int tl, int tr){
        unlazy(node, tl, tr);
        if(l > tr or r < tl) return;
        if(l <= tl and tr <= r){
            lazy[node] += val;
            unlazy(node, tl, tr);

          return;
        }
 
        int mid = (tl+tr)/2;
        update(2*node, l, r, val, tl, mid);
        update(2*node+1, l, r, val, mid+1, tr);
        tree[node] = join(tree[2*node], tree[2*node+1]);
 
        return;
    }
 
    int query(int node, int l, int r, int tl, int tr){
        if(l > tr or r < tl) return 0;
        if(l <= tl and tr <= r){
            unlazy(node, tl, tr);
            return tree[node];
        }
 
        unlazy(node, tl, tr);
 
        int mid = (tl+tr)/2;
        return join(query(2*node, l, r, tl, mid), query(2*node+1, l, r, mid+1, tr));
    }
} seg;
