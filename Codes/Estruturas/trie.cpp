struct Trie{
    const int B = 30;
    struct Node{
        Node* filho[2];
        Node(){
            filho[0] = filho[1] = NULL;
        }
    } *root;
    Trie(){
        root = new Node();
    }
    void add(int x){
        Node* cur = root;
        for(int i = B;i >= 0;i--){
            int t = ((x >> i) & 1);
            if(cur -> filho[t] == NULL) cur -> filho[t] = new Node();
            cur = cur -> filho[t];
        }
    }
    int query(int x){
        Node* cur = root;
        int res = 0;
        for(int i = B;i >= 0;i--){
            int t = ((x >> i) & 1)^1;
            if(cur -> filho[t] != NULL){
                res ^= (1 << i);
                cur = cur -> filho[t];
            }
            else{
                if(cur -> filho[(t+1) % 2] == NULL) break;
                cur = cur -> filho[(t+1) % 2];
            }
        }
        return res;
    }
} trie;
