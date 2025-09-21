struct BIT2D{
    int tree[N][N];
    void add(int x, int y, int val){
        while(x < N){
            int aty = y;
            while(aty < N){
                tree[x][aty] += val;
                aty += ((aty) & (-aty));
            }
            x += ((x) & (-x));
        }
        return;
    }
    int sum(int x, int y){
        int s = 0;
        while(x >= 1){
            int aty = y;
            while(aty >= 1){
                s += tree[x][aty];
                aty -= ((aty) & (-aty));
            }
            x -= ((x) & (-x));
        }
        return s;
    }
} bit;
