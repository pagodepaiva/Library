// Problem: https://codeforces.com/edu/course/2/lesson/5/1/practice/contest/279634/problem/C
#include<bits/stdc++.h>
#define int long long 
#define ms(v) memset(v, -1, sizeof v)
#define pi pair<int, int>
#define pb push_back
#define fr first
#define sc second
#define srt(v) sort(v.begin(), v.end())
#define INF 1e15
#define mp make_pair
#define N 100010

using namespace std;

int n, m;

struct Segtree{
	int tree[8*N];
	int lazy[8*N];

	int join(int a, int b){
		return a+b;
	}

	void unlazy(int node, int l, int mid, int r){
		if(lazy[node] != -1){
			tree[2*node] = (mid-l+1)*lazy[node];
			tree[2*node+1] = (r-mid)*lazy[node];
			lazy[2*node] = lazy[2*node+1] = lazy[node];
			lazy[node] = -1;
		}

		return;
	}

	void build(int node, int l, int r){
		if(l == r){
			tree[node] = 0;
			lazy[node] = -1;
			return;
		}

		int mid = (l+r) >> 1;

		build(2*node, l, mid);
		build(2*node+1, mid+1, r);

		tree[node] = join(tree[2*node], tree[2*node+1]);
		lazy[node] = -1;
		return;
	}

	void update(int node, int l, int r, int tl, int tr, int val){
		int mid = (tl+tr) >> 1;
		unlazy(node, tl, mid, tr);

		if(l > tr or r < tl) return;
		if(l <= tl and tr <= r){
			tree[node] = (tr-tl+1)*val;
			lazy[node] = val;
			unlazy(node, tl, mid, tr);
			return;
		}

		update(2*node, l, r, tl, mid, val);
		update(2*node+1, l, r, mid+1, tr, val);

		tree[node] = join(tree[2*node], tree[2*node+1]);
		return;
	}

	int query(int node, int l, int r, int tl, int tr){
		int mid = (tl+tr) >> 1;
		unlazy(node, tl, mid, tr);
		if(l > tr or r < tl) return 0;
		if(l <= tl and tr <= r) return tree[node];

		return join(query(2*node, l, r, tl, mid), query(2*node+1, l, r, mid+1, tr));
	}
} seg;

int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	seg.build(1, 1, n);

	for(int i = 0;i < m;i++){
		int a;
		cin >> a;

		if(a == 1){
			int l, r, v;
			cin >> l >> r >> v;
			l++;
			seg.update(1, l, r, 1, n, v);
		}

		if(a == 2){
			int l;
			cin >> l;
			l++;
			cout << seg.query(1, l, l, 1, n) << "\n";
		}
	}

	return 0;	
}
