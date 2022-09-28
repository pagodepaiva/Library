// problem: https://cses.fi/problemset/result/4708030/
#include<bits/stdc++.h>
#define int long long 
#define ms(v) memset(v, -1, sizeof v)
#define pi pair<int, int>
#define pb push_back
#define fr first
#define sc second
#define srt(v) sort(v.begin(), v.end())
#define INF 1e15
#define N 200010

using namespace std;

int n, sz;
int q;
int v[N];
int freq[N];

struct Query{
	int l, r, block;

	bool operator < (Query& q2){
		if(block < q2.block) return true;
		if(block > q2.block) return false;
		return r < q2.r;
	}
};

bool comp(pair <Query, int> a, pair <Query, int> b){
	if(a.fr < b.fr) return true;
	if(b.fr < a.fr) return false;
	return a.sc > b.sc;
}

vector <pair <Query, int>> qr;

void compress(){
	map <int, int> m;
	vector <pi> sorted;

	for(int i = 0;i < n;i++){
		sorted.pb({v[i], i});
	}

	srt(sorted);

	for(int i = 0;i < n;i++){
		if(m[sorted[i].fr] == 0){
			m[sorted[i].fr] = i+1;
		}

		v[sorted[i].sc] = m[sorted[i].fr];
	}

	return;
}

int solve(int l, int r, int tl, int tr, int res){
	while(l < tl){
		if(freq[v[l]] == 1){
			res--;
		}

		freq[v[l]]--;
		l++;
	}

	while(l > tl){
		if(freq[v[l-1]] == 0){
			res++;
		}

		freq[v[l-1]]++;
		l--;
	}

	while(r < tr){
		if(freq[v[r+1]] == 0){
			res++;
		}
		freq[v[r+1]]++;
		r++;
	}

	while(r > tr){
		if(freq[v[r]] == 1){
			res--;
		}
		freq[v[r]]--;
		r--;
	}

	return res;
}

int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);
	
	cin >> n >> q;
	sz = (int) sqrt(n);

	for(int i = 0;i < n;i++){
		cin >> v[i];
	}

	compress();

	for(int i = 0;i < q;i++){
		int a, b;
		cin >> a >> b;
		a--;
		b--;

		Query aux;
		aux.l = a;
		aux.r = b;
		aux.block = a/sz;

		qr.pb({aux, i});
	}

	sort(qr.begin(), qr.end(), comp);

	int l = 0;
	int r = 0;
	freq[v[0]]++;
	int res = 1;

	vector <pi> resp;

	for(int i = 0;i < q;i++){
		int lt = qr[i].fr.l;
		int rt = qr[i].fr.r;

		res = solve(l, r, lt, rt, res);
		l = lt;
		r = rt;
		resp.pb({qr[i].sc, res});
	}

	srt(resp);

	for(auto v : resp){
		cout << v.sc << "\n";
	}

	return 0;	
}
