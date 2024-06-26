vector <int> g[N];
int tin[N];
int con = 1;
int low[N];
set <pair <int, int>> dfstree;

void dfs(int v, int p){
    tin[v] = con;
    low[v] = tin[v];
    con++;
    for(auto x : g[v]){
        if(x == p) continue;
        if(tin[x] != 0){
            low[v] = min(low[v], tin[x]);
            continue;
        } 
        dfstree.insert({x, v});
        dfstree.insert({v, x});
        dfs(x, v);
        low[v] = min(low[v], low[x]);
    }
    return;
}
