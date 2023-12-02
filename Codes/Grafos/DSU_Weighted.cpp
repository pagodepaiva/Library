//
int n;
const int N = ;
//

struct DSU{
    int pai[N], sz[N], peso[N];

    void init(){
        for(int i = 1;i <= n;i++){
            pai[i] = i;
            sz[i] = 1;
            peso[i] = 0;
        }
    }

    int find(int x){
        if(x == pai[x]) return x;

        int p = find(pai[x]);
        peso[x] = peso[x] + peso[pai[x]];
        return pai[x] = p;
    }

    bool join(int a, int b, int d){
        int pa = find(a), pb = find(b);

        if(pa == pb) return ((peso[b] - peso[a]) == d);
        if(sz[pa] > sz[pb]){
            d *= -1;
            swap(a, b);
            swap(pa, pb);
        }

        pai[pa] = pb;
        sz[pb] += sz[pa];
        peso[pa] = peso[b] - peso[a] - d;

        return true;
    }

} dsu;
