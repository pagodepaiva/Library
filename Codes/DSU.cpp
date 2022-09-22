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
#define N 100010

using namespace std;

int n, m;


struct DSU{
    int pai[N], sz[N], comp, maxsz;

    DSU(){
        maxsz = 1;
        for(int i = 1;i <= N;i++){
            pai[i] = i;
            sz[i] = 1;
        }
    }

    int find(int x){
        return pai[x] = (x == pai[x] ? x : find(pai[x]));
    }

    void join(int a, int b){
        a = find(a);
        b = find(b);

        if(a == b) return;
        comp--;
        if(sz[a] > sz[b]) swap(a, b);

        pai[a] = b;
        sz[b] += sz[a];
        maxsz = max(maxsz, sz[b]);

        return;
    }
} dsu;

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);
    
    cin >> n >> m;

    dsu.comp = n;

    for(int i = 1;i <= m;i++){
        int a, b;
        cin >> a >> b;

        dsu.join(a, b);
        cout << dsu.comp << " " << dsu.maxsz << "\n";
    }

    return 0;
}
