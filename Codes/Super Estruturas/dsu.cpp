// Link: https://cses.fi/problemset/task/1676

#include<bits/stdc++.h>

using namespace std;

const int N = 200010;

struct DSU{
    int pai[N], sz[N];
    int tot, mxsz;
    void build(int n){
        for(int i = 1;i <= n;i++){
            pai[i] =i;
            sz[i] = 1;
        }
        tot = n;
        mxsz=1;
    }
    int find(int x){
        return pai[x] = (x == pai[x] ? x :find(pai[x]));
    }
    void join(int a, int b){
        a = find(a);
        b = find(b);
        if(a == b) return;
        tot--;
        if(sz[a] > sz[b]) swap(a, b);
        sz[b] += sz[a];
        pai[a] = b;
        mxsz = max(mxsz, sz[b]);
        return;
    }
} dsu;

int main(){
    int n, m;
    cin >> n >> m;
    dsu.build(n);
    while(m--){
        int a, b;
        cin >> a >> b;
        dsu.join(a, b);
        cout << dsu.tot << ' ' << dsu.mxsz << '\n';
    }
}
