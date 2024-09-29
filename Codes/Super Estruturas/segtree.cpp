// Link: https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/A

#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N = 100010;
int v[N];

struct Segtree{
    int tree[4*N];
    int join(int a, int b){
        return a+b;
    }
    void build(int node, int l, int r){
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
    void update(int node, int l, int r, int pos, int val){
        if(l == r){
            tree[node] = val;
            return;
        }
        int mid = (l+r)/2;
        if(l <= pos and pos <= mid) update(2*node, l, mid, pos, val);
        else update(2*node+1, mid+1, r, pos, val);
        tree[node] = join(tree[2*node], tree[2*node+1]);
        return;
    }
    int query(int node, int l, int r, int tl, int tr){
        if(l > tr or tl > r) return 0;
        if(l <= tl and tr <= r) return tree[node];
        int mid = (tl+tr)/2;
        return join(query(2*node, l, r, tl, mid), query(2*node+1, l, r, mid+1, tr));
    }
} seg;

int32_t main(){
    int n, m;
    cin >> n >> m;
    for(int i = 1;i <= n;i++)
        cin >> v[i];
    seg.build(1, 1, n);
    for(int i = 0;i < m;i++){
        int t;
        cin >> t;
        if(t == 1){
            int pos, val;
            cin >> pos >> val;
            pos++;
            seg.update(1, 1, n, pos, val);
        }
        else{
            int l, r;
            cin >> l >> r;
            l++;
            cout << seg.query(1, l, r, 1, n) << '\n';
        }
    }
}
