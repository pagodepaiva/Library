// Link: https://cses.fi/problemset/task/1647

#include<bits/stdc++.h>

using namespace std;

const int N = 200010;
const int LOGN = 20;
int v[N];
int n;

struct Sparse_Table{
    int sparse[N][LOGN];
    int lg[N];
    void build(){
        for(int i = 2;i <= n;i++){
            lg[i] = lg[i/2]+1;
            sparse[i][0] = v[i];
        }
        sparse[1][0] = v[1];
        for(int j = 1;j < LOGN;j++){
            for(int i = 1;i <= n;i++){
                sparse[i][j] = min(sparse[i][j-1], sparse[min(n, i+(1 << (j-1)))][j-1]);
                //cout << sparse[i][j] << ' ';
            }
            //cout << '\n';
        }
    }
    int query(int l, int r){
        int tam = r-l+1;
        //cout << l << ' ' << r << ' ' << tam << ' ' << lg[tam] << ' ' << sparse[l][lg[tam]] <<'\n';
        return min(sparse[l][lg[tam]], sparse[r-(1 << lg[tam]) +1][lg[tam]]);
    }
} sparse;

int main(){
    int q;cin >> n >> q;
    for(int i = 1;i <= n;i++)
        cin >> v[i];
    sparse.build();
    while(q--){
        int l, r;
        cin >> l >> r;
        cout << sparse.query(l, r) << '\n';
    }
}
