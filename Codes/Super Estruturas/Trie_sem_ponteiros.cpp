struct Trie{
    int cnt[32*N], trie[32*N][2], ver;
    Trie(){
        ver = 1;
        memset(trie, -1, sizeof trie);
        memset(cnt, 0, sizeof cnt);
    }
    void clear(int v = 0){
        if(trie[v][0] != -1) clear(trie[v][0]);
        if(trie[v][1] != -1) clear(trie[v][1]);
        trie[v][0] = trie[v][1] = -1;
        cnt[v] = 0;
    }
    int sum(int idx){
        if(idx == -1) return 0;
        return cnt[idx];
    }
    void add(int x, int bit, int v){
        if(bit == -1){
            cnt[v]++;
            return;
        }
        int b = (1<<bit);
        if((x&b)){
            if(trie[v][1] == -1){
                trie[v][1] = ver;
                ver++;
            }
            add(x, bit-1, trie[v][1]);
        }
        else{
            if(trie[v][0] == -1){
                trie[v][0] = ver;
                ver++;
            }
            add(x, bit-1, trie[v][0]);
        }
        cnt[v] = sum(trie[v][0])+sum(trie[v][1]);
        return;
    }
    void remove(int x, int bit, int v){
        if(bit == -1){
            cnt[v]--;
            return;
        } 
        int b = (1<<bit);
        if((x&b)){
            if(trie[v][1] == -1){
                trie[v][1] = ver;
                ver++;
            }
            remove(x, bit-1, trie[v][1]);
        }
        else{
            if(trie[v][0] == -1){
                trie[v][0] = ver;
                ver++;
            }
            remove(x, bit-1, trie[v][0]);
        }
        cnt[v] = sum(trie[v][0])+sum(trie[v][1]);
        return;
    }
    int query(int x){
        int ans = 0;
        int v = 0;
        for(int bit = 30;bit >= 0;bit--){
            int b = (1<<bit);
            if((x&b)){
                if(sum(trie[v][0])){
                    ans |= (1<<bit);
                    v = trie[v][0];
                }
                else{
                    v = trie[v][1];
                }
            }
            else{
                if(sum(trie[v][1])){
                    ans |= (1<<bit);
                    v = trie[v][1];
                }
                else{
                    v = trie[v][0];
                }
            }
        }
        return ans;
    }
} trie;
