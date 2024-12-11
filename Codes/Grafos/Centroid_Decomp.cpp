#include<bits/stdc++.h>

using namespace std;

const int N = 100010;
const int LOGN = 20;
int n, m;
vector <int> g[N];
int centroid[N];
int sz[N];
int mark[N];
int dist[N][LOGN];
int con[N];
int h[N];
int res[N];

void dfs(int v, int p){
    sz[v] = 1;
    for(auto x : g[v]){
        if(x == p) continue;
        if(mark[x]) continue;
        dfs(x, v);
        sz[v] += sz[x];
    }
    return;
}

int tam;

int find_centroid(int v, int p){
    for(auto x : g[v]){
        if(x == p) continue;
        if(mark[x]) continue;
        if(2*sz[x] > tam) return find_centroid(x, v);
    }
    return v;
}

void calc_dist(int v, int p){
    for(auto x : g[v]){
        if(p == x) continue;
        if(mark[x]) continue;
        dist[x][con[x]] = h[x] = h[v]+1;
        con[x]++;
        calc_dist(x, v);
    }    
    return;
}

void decomp(int v = 1, int p = -1){
    dfs(v, v);
    tam = sz[v];
    int c = find_centroid(v, v);
    h[c] = 0;
    calc_dist(c, c);
    mark[c] = 1;
    centroid[c] = (p == -1 ? c : p);
    for(auto x : g[c]){
        if(mark[x]) continue;
        decomp(x, c);
    }
    return;
}

void update(int v){
    res[v] = 0;
    int cc = con[v]-1;
    int vv = v;
    int cnt = 0;
    while(centroid[v] != v){
        cnt++;
        v = centroid[v];
        res[v] = min(res[v], dist[vv][cc]);
        cc--;
    }
    return;
}

int query(int v){
    int cnt = 0;
    int ans = res[v];
    int cc = con[v]-1;
    int vv = v;
    while(centroid[v] != v){
        cnt++;
        v = centroid[v];
        ans = min(ans, res[v]+dist[vv][cc]);
        cc--;
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    int n, m;
    cin >> n >> m;
    for(int i = 1;i < n;i++){
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    decomp();
    for(int i = 1;i <= n;i++){
        res[i] = 10*N;
    }
    update(1);
    while(m--){
        int t, v;
        cin >> t >> v;
        if(t == 1) update(v);
        else cout << query(v) << '\n';
    }
    return 0;
}
