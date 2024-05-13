struct Node{
    int val;
    Node *lt, *rt;
    Node(){
        val = 0;
        lt = rt = NULL;
    }
    void update(int pos, int v, int l, int r){
        if(l == r){
            val += v;
            return;
        }
        int mid = (l+r)/2;
        if(l <= pos and pos <= mid){
            if(!lt) lt = new Node();
            lt->update(pos, v, l, mid);
        }
        else{
            if(!rt) rt = new Node();
            rt->update(pos, v, mid+1, r);
        }
        val = 0;
        if(lt) val += lt->val;
        if(rt) val += rt->val;
        return;
    }
    int query(int l, int r, int tl, int tr){
        if(l <= tl and tr <= r) return val;
        if(l > tr or tl > r) return 0;
        int mid = (tl+tr)/2;
        int res = 0;
        if(lt) res += lt->query(l, r, tl, mid);
        if(rt) res += rt->query(l,r,mid+1,tr);
        return res;
    }
} seg;
