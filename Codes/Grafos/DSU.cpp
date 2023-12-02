//
int n;
const int N = ;
//

struct DSU{
    int pai[N], sz[N];

    DSU(){
        for(int i = 1;i < N;i++){
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
        if(sz[a] > sz[b]) swap(a, b);

        pai[a] = b;
        sz[b] += sz[a];
        return;
    }
} dsu;
