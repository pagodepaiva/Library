// Link:https://cses.fi/problemset/result/10667983/

#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N = 200010;
int v[N];

struct BIT{
    int tree[N];
    void update(int pos, int val){
        while(pos < N){
            tree[pos] += val;
            pos += (pos & (-pos));
        }
        return;
    }
    int query(int pos){
        int sum = 0;
        while(pos > 0){
            sum += tree[pos];
            pos -= (pos & (-pos));
        }
        return sum;
    }
} bit;

int query(int l, int r){
    return bit.query(r) - bit.query(l-1);
}

int32_t main(){
    int n;
    cin >> n;
    int q;
    cin >> q;
    for(int i = 1;i <= n;i++){
        int x;
        cin >> x;
        bit.update(i, x);
        v[i] = x;
    }
    while(q--){
        int t;
        cin >> t;
        if(t == 1){
            int pos, val;
            cin >> pos >> val;
            bit.update(pos, val-v[pos]);
            v[pos] = val;
        }
        else{
            int a, b;
            cin >> a >> b;
            cout << query(a, b) << '\n';
        }
    }
}
