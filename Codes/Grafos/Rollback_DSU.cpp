//
int n;
const int N = ;
//

struct DSU{
    int pai[N], sz[N];
    stack <pair <int, int>> s;

    DSU(){
        for(int i = 1;i < N;i++){
            pai[i] = i;
            sz[i] = 1;
        }
        s.push({0, 0});
        // res = n;
    }

    int find(int x){
        return (x == pai[x] ? x : find(pai[x]));
    }

    void join(int a, int b){
        a = find(a);
        b = find(b);

        if(a == b) return;
        if(sz[a] > sz[b]) swap(a, b);

        s.push({a, b});
        pai[a] = b;
        sz[b] += sz[a];
        // res--;
        return;
    }

    void save(){
        s.push({0, 0});
    }

    void rollback(){
        while(s.top() != make_pair(0, 0)){
            auto [a, b] = s.top();
            s.pop();

            pai[a] = a;
            sz[b] -= sz[a]; 
            // res++;
        }

        s.pop();

        if(s.size() == 0) s.push({0, 0});
    }
} dsu;
