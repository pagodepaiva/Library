#include<bits/stdc++.h>

using namespace std;

const int N = 300010;

struct DSU{
    int pai[N], sz[N], res;
    stack <array <int, 4>> rollback;
    void build(int n){
        res = n;
        for(int i = 0;i < N;i++){
            pai[i] = i;
            sz[i] = 1;
        }
    }
    int find(int x){
        return (x == pai[x] ? x : find(pai[x]));
    }
    void join(int a, int b){
        a = find(a);
        b = find(b);
        if(a == b){
            rollback.push({-1, -1, -1, -1});
            return;
        }
        if(sz[a] > sz[b]) swap(a, b);
        rollback.push({a, b, pai[a], sz[a]});
        pai[a] = b;
        sz[b] += sz[a];
        res--;
        return;
    }
    void roll(    ){
        auto [a, b, pa, sza] = rollback.top();
        rollback.pop();
        if(a == -1) return;
        pai[a] = a;
        sz[b] -= sz[a];
        res++;
    }
} dsu;

void solve(int tl, int tr, vector <array <int, 4>> queries){
    if(queries.empty()) return;
    if(tl == tr){
        int con = 0;
        for(auto [l, r, a, b] : queries){
            if(l <= tl and tr <= r){
                if(a > 0) {
                    dsu.join(a, b);
                    con++;
                }
            }
            if(l > tr or tl > r) continue;
        }
        for(auto [l, r, a, b] : queries){
            if(a == 0 and l == tl) cout << dsu.res << '\n';
        }
        while(con--){
            dsu.roll();
        }
        return;
    }
    int mid = (tl+tr)/2;
    vector <array <int, 4>> q2;
    vector <array <int, 4>> q3;
    int con = 0;
    for(auto [l, r, a, b] : queries){
        if(l <= tl and tr <= r){
            if(a > 0) {
                dsu.join(a, b);
                con++;
            }
            continue;
        }
        if(l > tr or tl > r) continue;
        if(!(l > mid or tl > r)) q2.push_back({l, r, a, b});
        if(!(l > r or tl > mid+1)) q3.push_back({l, r, a, b});
    }
    solve(tl, mid, q2);
    solve(mid+1, tr, q3);
    while(con--){
        dsu.roll();
    }
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    int n, q;
    cin >> n >> q;
    dsu.build(n);
    int t = 1;
    map <pair <int, int>, int> m;
    vector <array <int, 4>> qr;
    while(q--){
        char c;
        cin >> c;
        if(c == '?'){
            qr.push_back({t, t, 0, 0});
        }
        else if(c == '+'){
            int a, b;
            cin >> a >> b;
            m[{a, b}] = t;
            m[{b, a}] = t;
        }
        else{
            int a, b;
            cin >> a >> b;
            qr.push_back({m[{a, b}], t, a, b});
            m.erase({a, b});
            m.erase({b, a});
        }
        t++;
    }
    for(auto [p, x] : m){
        auto [a, b] = p;
        qr.push_back({x, t, a, b});
    }
    solve(1, t-1, qr);
}
