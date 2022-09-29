// Problem: https://cses.fi/problemset/result/4713844/
#include<bits/stdc++.h>
#define int long long 
#define ms(v) memset(v, -1, sizeof v)
#define pi pair<int, int>
#define pb push_back
#define fr first
#define sc second
#define srt(v) sort(v.begin(), v.end())
#define INF 1e15
#define N 2510
 
using namespace std;
 
int n, m;
vector <int> g[N];
int dist[N];
 
int bfs(int st){
	ms(dist);
	dist[st] = 0;
	queue <pi> q;
	q.push({st, st});
 
	int res = INF;
 
	while(!q.empty()){
		int v = q.front().fr, p = q.front().sc;
		q.pop();
 
		for(auto x : g[v]){
			if(x == p) continue;
			if(dist[x] != -1){
				res = min(res, dist[x] + dist[v] + 1);
			}
			else{
				dist[x] = dist[v] + 1;
				q.push({x, v});
			}
		}
	}
 
	return res;
}
 
int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;	
 
	for(int i = 0;i < m;i++){
		int a, b;
		cin >> a >> b;
		g[a].pb(b);
		g[b].pb(a);
	}
 
	int minx = INF;
 
	for(int i = 1;i <= n;i++){
		minx = min(minx, bfs(i));
	}
 
	if(minx == INF){
		cout << -1 << "\n";
		return 0;
	}
 
	cout << minx << "\n";
	return 0;	
}
