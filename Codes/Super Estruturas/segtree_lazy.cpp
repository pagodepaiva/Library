// Link: https://codeforces.com/edu/course/2/lesson/5/2/practice/contest/279653/problem/D

#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N = 100010;
int v[N];

struct Segtree{
    int tree[4*N], lazy[4*N];
    int join(int a, int b){
        return a+b;
    }
    void unlazy(int node, int l, int r){
        tree[node] += (r-l+1)*lazy[node];
        if(l != r){
            lazy[2*node] += lazy[node];
            lazy[2*node+1] += lazy[node];
        }
        lazy[node] = 0;
    }
    void build(int node, int l, int r){
        lazy[node] = 0;
        if(l == r){
            tree[node] = v[l];
            return;
        }
        int mid = (l+r)/2;
        build(2*node, l, mid);
        build(2*node+1, mid+1, r);
        tree[node] = join(tree[2*node], tree[2*node+1]);
        return;
    }
    void update(int node, int l, int r, int tl, int tr, int val){
        unlazy(node, tl,tr);
        if(l > tr or tl > r) return;
        if(l <= tl and tr <= r){
            lazy[node] += val;
            unlazy(node, tl, tr);
            return;
        }
        int mid = (tl+tr)/2;
        update(2*node, l, r, tl, mid, val);
        update(2*node+1, l, r, mid+1, tr, val);
        tree[node] = join(tree[2*node],tree[2*node+1]);
        return;
    }
    int query(int node, int l, int r, int tl, int tr){
        unlazy(node, tl, tr);
        if(l > tr or tl > r) return 0;
        if(l <= tl and tr <= r) return tree[node];
        int mid = (tl+tr)/2;
        return join(query(2*node, l, r, tl, mid), query(2*node+1, l, r, mid+1, tr));
    }
} seg;

int32_t main(){
    int n, m;
    cin >> n >> m;
    seg.build(1, 1, n);
    for(int i = 0;i < m;i++){
        int t;
        cin >> t;
        if(t == 1){
            int l, r, val;
            cin >> l >> r >> val;
            l++;
            seg.update(1, l, r, 1, n, val);
        }
        else{
            int l, r;
            cin >> l >> r;
            l++;
            cout << seg.query(1, l, r, 1, n) << '\n';
        }
    }
}
