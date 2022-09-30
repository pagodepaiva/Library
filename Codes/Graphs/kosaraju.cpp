// Problem: https://cses.fi/problemset/task/1683/
#include<bits/stdc++.h>
#define int long long 
#define ms(v) memset(v, -1, sizeof v)
#define pi pair<int, int>
#define pb push_back
#define fr first
#define sc second
#define srt(v) sort(v.begin(), v.end())
#define INF 1e15
#define N 100010

using namespace std;

int n, m;
int con;
vector <int> g[N];
vector <int> gt[N];
int mark[N];
stack <int> s;

void dfs1(int x){
	if(mark[x] != 0) return;
	mark[x] = 1;

	for(auto v : g[x]){
		dfs1(v);
	}

	s.push(x);

	return;
}

void dfs2(int x){
	if(mark[x] != 0) return;
	mark[x] = con;

	for(auto v : gt[x]){
		dfs2(v);
	}

	return;
}

int32_t main(){
	// ios::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;

	for(int i = 1;i <= m;i++){
		int a, b;
		cin >> a >> b;
		g[a].pb(b);
		gt[b].pb(a);
	}

	for(int i = 1;i <= n;i++){
		dfs1(i);
	}
	memset(mark, 0, sizeof mark);

	while(!s.empty()){
		int v = s.top();
		s.pop();
		// cout << v << " ";
		if(mark[v] != 0) continue;
		con++;
		dfs2(v);
	}

	cout << con << "\n";
	for(int i = 1;i <= n;i++){
		cout << mark[i] << " ";
	}

	cout << "\n";

	return 0;	
}
