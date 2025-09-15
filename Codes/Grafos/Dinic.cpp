struct FlowEdge{
    int v, u;
    ll cap, flow = 0;
    FlowEdge(int v, int u, ll cap) : v(v), u(u), cap(cap) {}
};

struct Dinic{
    const ll flow_inf = 1e18;
    vector <FlowEdge> edges;
    vector <vector <int>> adj;
    int n, m = 0;
    int s, t;
    vector <int> level, ptr;
    queue <int> q;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n+1);
        level.resize(n+1);
        ptr.resize(n+1);
    }

    void add_edge(int v, int u, ll cap){
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m+1);
        m += 2;
    }

    bool bfs(){
        while(!q.empty()){
            int v = q.front();
            q.pop();
            for (auto id : adj[v]){
                if(edges[id].cap == edges[id].flow) // aresta saturada
                    continue;
                if(level[edges[id].u] != -1) // aresta mais distante no grafo de bfs
                    continue;
                level[edges[id].u] = level[v]+1;
                q.push(edges[id].u);
            }
        }
        return (level[t] != -1); // se der -1 entao nao temos mais flow
    }

    ll dfs(int v, ll pushed){
        // pushed eh quanto de flow nos trouxemos para v
        if(pushed == 0)
            return 0;
        if(v == t)
            return pushed;
        for(int& cid = ptr[v]; cid < adj[v].size();cid++){ // colocamos int& para mudarmos ptr[v] e nao ter que repetir arestas nao utilizadas
            int id = adj[v][cid];
            int u = edges[id].u;
            if(level[v] + 1 != level[u])
                continue;
            ll tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if(tr == 0) // nao conseguimos leval flow para t
                continue;
            edges[id].flow += tr;
            edges[id^1].flow -= tr;
            return tr;
        }
        return 0;
    }

    ll flow(){
        ll f = 0;
        while(true){
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if(!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while( ll pushed = dfs(s, flow_inf)){
                //cout << pushed << endl;
                f += pushed;
            }
        }
        return f;
    }
};
