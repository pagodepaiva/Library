const int N = 510;
const ll INF = 1e18;

struct Ford_Fulkerson{
    // o(VE^2)
    int n;
    ll cap[N][N];
    int pai[N];
    vector <int> g[N];
    Ford_Fulkerson(){
        for(int i = 0;i < N;i++){
            for(int j = 0;j < N;j++){
                cap[i][j] = 0;
            }
        }
    }
    void add(int a, int b, ll c){
        cap[a][b] += c;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    ll bfs(int s, int t){
        memset(pai, -1, sizeof pai);
        pai[s] = -2;
        queue <pair <int, ll>> q;
        q.push({s, INF});
        while(!q.empty()){
            int v = q.front().fr;
            ll flow = q.front().sc;
            q.pop();

            for(auto x : g[v]){
                if(pai[x] == -1 and cap[v][x]){
                    pai[x] = v;
                    ll new_flow = min(flow, cap[v][x]);
                    if(x == t)
                        return new_flow;
                    q.push({x, new_flow});
                }
            }
        }
        return 0;
    }

    ll maxflow(int s, int t){
        ll flow = 0;
        ll new_flow;

        while(new_flow = bfs(s, t)){
            flow += new_flow;
            int v = t;
            while(v != s){
                int prev = pai[v];
                cap[prev][v] -= new_flow;
                cap[v][prev] += new_flow;
                v = prev;
            }
        }
        return flow;
    }
} solve;

