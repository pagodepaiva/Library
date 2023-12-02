// 
const int N = ;
const int LOGN  = ;
int n;
vector <int> g[N];
//

int pai[N][LOGN];
int h[N];

void dfs(int v, int p){
    pai[v][0] = p;

    for(auto x : g[v]){
        if(x == p) continue;
        h[x] = h[v]+1;
        dfs(x, v);
    }

    return;
}

void build(){
    dfs(1, 1);
    for(int i = 1;i <= n;i++){
        for(int j = 1;j < LOGN;j++){
            pai[i][j] = pai[pai[i][j-1]][j-1];
        }
    }

    return;
}

int lca(int x, int y){
    if(h[x] > h[y]) swap(x, y);

    int t = h[y] - h[x];

    for(int i = LOGN-1;i >= 0;i--){
        if((t & (1 << i)) != 0){
            y = pai[y][i];
        }
    }

    if(x == y) return x;

    for(int i = LOGN-1;i >= 0;i--){
        if(pai[x][i] == pai[y][i]) continue;
        x = pai[x][i];
        y = pai[y][i];
    }

    return pai[x][0];
}

int dist(int v, int t){
    for(int i = LOGN-1;i >= 0;i--){
        if((t & (1 << i)) != 0){
            v = pai[v][i];
        }
    }

    return v;
}
