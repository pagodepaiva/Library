#include<bits/stdc++.h>
#define int long long
#define ms(v) memset(v, -1, sizeof v)
#define pb push_back
#define mp make_pair
#define ll long long int
#define pi pair <int,int>
#define itn int
#define fr first
#define sc second
#define srt(v) sort(v.begin(), v.end())
#define rvs(v) reverse(v.begin(), v.end())
#define mod 1000000007
#define INF 1e18
#define N 200010
#define LOGN 20

using namespace std;

int n, q;
int pai[N][LOGN+5];
int dist[N];
vector <int> g[N];

void dfs(int x, int p){
    for(int i = 1; i < LOGN;i++){
        pai[x][i] = pai[pai[x][i-1]][i-1];
    } 
    
    for(auto v : g[x]){
        if(v == p) continue;
        pai[v][0] = x;
        dist[v] = dist[x] + 1;
        dfs(v, x);
    }

    return;
}

int jump(int x, int d){
    for(int i = 0;i < LOGN;i++){
        // cout << x << " ";
        if((d >> i) & 1){
            x = pai[x][i];
        }
    }

    return x;
}

int LCA(int a, int b){
    if(dist[a] < dist[b]) swap(a, b);

    a = jump(a, dist[a] - dist[b]);

    if(a == b) return a;
    // cout << a << " ";

    for(int i = LOGN-1;i >= 0;i--){
        int at = pai[a][i], bt = pai[b][i];

        if(at != bt){
            a = at; b = bt;
        }
    }

    return pai[a][0];
}

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> q;

    for(int i = 1;i < n;i++){
        int a, b;
        cin >> a >> b;

        g[a].pb(b);
        g[b].pb(a);
    }

    pai[1][0] = 1;

    dfs(1, 1);

    for(int i = 1;i <= q;i++){
        int a, b, c;
        cin >> a >> b;
        c = LCA(a, b);

        // cout << c << " ";
        cout << dist[a] + dist[b] - 2*dist[c] << "\n";
    }

    return 0;
}
