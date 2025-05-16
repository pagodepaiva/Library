#include<bits/stdc++.h>
#define int long long
#define pii pair <int, int>
#define fr first
#define sc second

using namespace std;

const int N = 200010;
int n;
vector <int> g[N];
pair <int, int> bst;
int sum;
int res;
int sz[N];

void dfs(int v, int p){
    sz[v] = 1;
    for(auto x : g[v]){
        if(x == p)
            continue;
        dfs(x, v);
        sz[v] += sz[x];
    }
    return;
}

void reroot(int v, int p){
    for(auto x : g[v]){
        if(v > x)
            continue;
        if(res < sum - max(0LL, min(sz[x], n-1-sz[x])) - max(0LL, min(sz[v], n-1-sz[v])) + max(0LL, min(sz[v]-1, (n-1)-(sz[v]-1)))){
            res = sum- max(0LL, min(sz[x], n-1-sz[x])) - max(0LL, min(sz[v], n-1-sz[v])) + max(0LL, min(sz[v]-1, (n-1)-(sz[v]-1)));
            bst = {v, x};
        }
    }
    for(auto x : g[v]){
        if(x == p)
            continue;
        sum -= max(0LL, min(sz[x], n-1-sz[x]));
        sum -= max(0LL, min(sz[v], n-1-sz[v]));
        sz[v] -= sz[x];
        sz[x] += sz[v];
        sum += max(0LL, min(sz[v], n-1 - sz[v]));
        sum += max(0LL, min(sz[x], n-1 - sz[x]));
        reroot(x, v);
        sum -= max(0LL, min(sz[x], n-1-sz[x]));
        sum -= max(0LL, min(sz[v], n-1-sz[v]));
        sz[x] -= sz[v];
        sz[v] += sz[x];
        sum += max(0LL, min(sz[x], n-1 - sz[x]));
        sum += max(0LL, min(sz[v], n-1 - sz[v]));
    }
    return;
}

int find_centroid(int v, int p){
    for(auto x : g[v]){
        if(x == p)
            continue;
        if(sz[x] > n/2)
            return find_centroid(x, v);
    }
    return v;
}

vector <int> comp[N];
int cor;

void dfs2(int v, int p){
    comp[cor].push_back(v);
    for(auto x : g[v]){
        if(x == p)
            continue;
        dfs2(x, v);
    }
}

int resposta[N];

void solve(){
    cin >> n;
    vector <pair <int, int>> arestas;
    for(int i = 1;i < n;i++){
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(1, 1);
    for(int i = 1;i <= n;i++){
        sum += max(0LL, min(sz[i], n-1 - sz[i]));
    }
    reroot(1, 1);
    cout << bst.first << ' ' << bst.second << '\n';
    //cout << res << '\n';
    if(bst.first > bst.second)
        swap(bst.first, bst.second);
    for(auto it = g[bst.first].begin(); it != g[bst.first].end();it++)
        if(*it == bst.second){
            g[bst.first].erase(it);
            break;
        }
    for(auto x : g[bst.second]){
        if(x == bst.first)
            continue;
        for(auto it = g[x].begin(); it != g[x].end();it++)
            if(*it == bst.second){
                g[x].erase(it);
                break;
            }
        g[bst.first].push_back(x);
        g[x].push_back(bst.first);
    }    
    n--;
    dfs(1, 1);
    int c = find_centroid(1, 1);
    dfs(c, c);
    priority_queue <pair <int, int>> pq;
    for(auto x : g[c]){
        dfs2(x, c);
        pq.push({comp[cor].size(), cor});
        cor++;
    }
    int cnt = 1;
    while(pq.size() > 1){
        auto [ta, a] = pq.top();
        pq.pop();
        auto [tb, b] = pq.top();
        pq.pop();
        resposta[comp[a].back()] = cnt;
        resposta[comp[b].back()] = cnt;
        cnt++;
        comp[a].pop_back();
        comp[b].pop_back();
        ta--;
        tb--;
        if(ta > 0)
            pq.push({ta, a});
        if(tb > 0)
            pq.push({tb, b});
    }
    resposta[comp[pq.top().second].back()] = cnt;
    resposta[c] = cnt;
    for(int i = 1;i <= n+1;i++){
        cout << resposta[i] << ' '; 
    }
    cout << '\n';
    for(int i = 0;i <= n+10;i++){
        g[i].clear();sz[i] = 0;
        comp[i].clear();
        resposta[i] = 0;
    }
    bst = {0, 0};sum = res = cor = 0;
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
