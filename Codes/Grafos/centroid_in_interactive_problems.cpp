#include<bits/stdc++.h>
#define int long long
#define pii pair <int, int>
#define fr first
#define sc second

using namespace std;

const int N = 100010;

int n;
vector <int> g[N];
int mark[N];
int sz[N];
int tam;

void calc(int v, int p){
    sz[v] = 1;
    for(auto x : g[v]){
        if(x == p){
            continue;
        }
        if(mark[x]){
            continue;
        }
        calc(x, v);
        sz[v] += sz[x];
    }
    return;
}

int find_centroid(int v, int p){
    for(auto x : g[v]){
        if(x == p)
            continue;
        if(mark[x])
            continue;
        if(sz[x] > tam/2)
            return find_centroid(x, v);
    }
    return v;
}

int query(int a, int b){
    cout << "? " << a << ' ' << b << '\n';
    cout << flush;
    int x;
    cin >> x;
    return x;
}

int find_raiz(int v){
    calc(v, v);
    tam = sz[v];
    int c = find_centroid(v, v);
    vector <pair <int,int>> raizes;
    for(auto x : g[c])
        if(mark[x] == 0)
            raizes.push_back({sz[x], x});
    sort(raizes.begin(), raizes.end());
    reverse(raizes.begin(), raizes.end());
    // a depender do problema, voce escolhe o que fazer com as possiveis novas raizes
    // Exemplo desse problema: https://codeforces.com/gym/105484/problem/G
    if(raizes.empty())
        return c;
    if(raizes.size() == 1){
        int t = query(raizes[0].second, c);
        if(t == 0){
            mark[c] = 1;
            return find_raiz(raizes[0].second);
        }
        else{
            return c;
        }
    }
    int t = query(raizes[0].second, raizes[1].second);
    if(t == 0){
        mark[c] = 1;
        return find_raiz(raizes[0].second);
    }
    else if(t == 1){
        mark[raizes[0].second] = 1;
        mark[raizes[1].second] = 1;
        return find_raiz(c);
    }
    else{
        mark[c] = 1;
        return find_raiz(raizes[1].second);
    }
}

void solve(){
    cin >> n;
    /*for(int i = 1;i < n;i++){
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }*/
    for(int i = 1;i <= n;i++){
        int a, b;
        cin >> a >> b;
        if(a != 0){
            g[a].push_back(i);
            g[i].push_back(a);
        }
        if(b != 0){
            g[b].push_back(i);
            g[i].push_back(b);
        }
    }
    int r = find_raiz(1);
    cout << "! " << r << '\n';
    cout << flush;
    for(int i = 1;i <= n;i++){
        g[i].clear();
        mark[i] = 0;
    }
    return;
}

int32_t main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
