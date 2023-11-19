#include<bits/stdc++.h>
#define int long long
#define N 100010
#define inf 1e5 + 10
using namespace std;

int n;
struct Line{
    int a[4];

    int query(int x){
        return a[0] + a[1]*x + a[2]*x*x + a[3]*x*x*x;
    }
} null;

struct Lichao{
    Line tree[4*N];

    void build(int node, int l, int r){
        if(l == r){
            tree[node] = null;
            return;
        }

        int mid = (l+r)/2;

        build(2*node, l, mid);
        build(2*node+1, mid+1, r);

        tree[node] = null;
        return;
    }

    void update(int node, int l, int r, Line s){
        if(l == r){
            if(s.query(l) < tree[node].query(l)) tree[node] = s;
            return;
        }

        int mid = (l+r)/2;

        if(s.query(l) < tree[node].query(l)) swap(s, tree[node]);
        if(s.query(mid) < tree[node].query(mid)){
            swap(s, tree[node]);
            update(2*node, l, mid, s);
        }
        else{
            update(2*node+1, mid+1, r, s);
        }
        
        return;
    }

    int query(int node, int l, int r, int v){
        if(l == r){
            return tree[node].query(l);
        }

        int mid = (l+r)/2;
        if(v <= mid){
            return min(tree[node].query(v), query(2*node, l, mid, v));
        }
        else{
            return min(tree[node].query(v), query(2*node+1, mid+1, r, v));
        }
    }
} seg;

vector <Line> v;
int res[N];

int32_t main(){
    null.a[0] = null.a[1] = null.a[2] = null.a[3] = inf;
    null.a[3] = 1e3+10;
    int t;
    cin >> t;
    while(t--){
        cin >> n;   
        int l1 = sqrt(1e5);
        int r1 = 1e5;

        seg.build(1, l1+1, r1);
        for(int i = 0;i <= l1;i++){
            res[i] = 1e18;
        }
        for(int i = 0;i < n;i++){
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            Line l = {a, b, c, d};
            for(int j = 0;j <= l1;j++){
                res[j] = min(res[j] ,a+b*j+c*j*j+d*j*j*j);
            }
            seg.update(1, l1+1, r1, l);
        }

        int q;
        cin >> q;

        for(int i = 0;i < q;i++){
            int x;
            cin >> x;
            if(0 <= x and x <= l1) cout << res[x] << '\n';
            else cout << seg.query(1, l1+1, r1, x) << '\n';
        }
    }
    
    return 0;
}
