vector <pair <int, int>> g[N];
int tin[N];
int con = 1;
int low[N];
int viz[N];
vector <pair <int, int>> arestas;
int bridges[N];

void dfs(int v, int p){
    tin[v] = con;
    low[v] = tin[v];
    con++;
    for(auto [x, _] : g[v]){
        if(x == p) continue;
        if(tin[x] != 0){
            low[v] = min(low[v], tin[x]);
            continue;
        }
        dfs(x, v);
        low[v] = min(low[v], low[x]);
    }
    return;
}

vector <int> gb[N];

void dfs_comprimir(int v, int cor){
    viz[v] = cor;
    for(auto [x, i] : g[v]){
        if(viz[x]) continue;
        if(bridges[i]) continue;
        dfs_comprimir(x, cor);
    }
    return;
}

void solve(){
    int n, m;
    cin >> n >> m;
    for(int i = 0;i < m;i++){
        int a, b;
        cin >> a >> b;
        g[a].push_back({b, i});
        g[b].push_back({a, i});
        arestas.push_back({a, b});
    }
    dfs(1, 1);
    int aux = 0;
    for(auto [a, b] : arestas){
        if(tin[a] > tin[b]) swap(a, b);
        if(low[b] > tin[a]){
            bridges[aux] = 1;
        }
        aux++;
    }
    int cor = 1;
    for(int i = 1;i <= n;i++){
        if(viz[i]) continue;
        dfs_comprimir(i, cor);
        cor++;
    }
    aux = -1;
    for(auto [a, b] : arestas){
        aux++;
        if(!bridges[aux]) continue;
        gb[viz[a]].push_back(viz[b]);
        gb[viz[b]].push_back(viz[a]);
    }
    return;
}
