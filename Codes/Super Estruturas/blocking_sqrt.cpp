// Link: https://cses.fi/problemset/task/1734

#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N = 200010;
const int B = 500;

int v[N];
struct Blocking{
    int block[N/B];
    void build(int n){
        memset(block, 0, sizeof block);
        for(int i = 0;i < n;i++){
            block[i/B] += v[i];
        }
    }
    void update(int pos, int val){
        block[pos/B] -= v[pos];
        block[pos/B] += val;
        v[pos] = val;
    }
    int query(int l, int r){
        int sum = 0;
        while(l <= r and (l % B) != 0){
            sum += v[l];
            l++;
        }
        while(l <= r and (r % B) != B-1){
            sum += v[r];
            r--;
        }
        while(l <= r){
            sum += block[l/B];
            l += B;
        }
        return sum;
    }
} block;

int32_t main(){
    int n, q;
    cin >> n >> q;
    for(int i = 0;i < n;i++){
        cin >> v[i];
    }
    block.build(n);
    while(q--){
        int t;
        cin >> t;
        if(t == 1){
            int pos, val;
            cin >> pos >> val;
            block.update(pos-1, val);
        }
        else{
            int l, r;
            cin >> l >> r;
            cout << block.query(l-1, r-1) << '\n';
        }
    }
}
