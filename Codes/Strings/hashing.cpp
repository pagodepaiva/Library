const int tam_hash = 1e6+10;
struct Hashing{
    long long binpow(long long a, long long b, long long m) {
        a %= m;
        long long res = 1;
        while (b > 0) {
            if (b & 1)
                res = res * a % m;
            a = a * a % m;
            b >>= 1;
        }
        return res;
    }
    const int p = 419;
    const int q = 233;
    const int m = 36893401;
    int potp[tam_hash], potq[tam_hash];
    int invp[tam_hash], invq[tam_hash];
    array <int, 2> prefhash[tam_hash];
    Hashing(){
        potp[0] = potq[0] = 1;
        invp[1] = binpow(p, m-2, m);
        invq[1] = binpow(q, m-2, m);
        invp[0] = invq[0] = 1;
        for(int i = 1;i < tam_hash;i++){
            potp[i] = potp[i-1]*p;
            potp[i] %= m;
            potq[i] = potq[i-1]*q;
            potq[i] %= m;
            if(i == 1) continue;
            invp[i] = invp[i-1]*invp[1];
            invp[i] %= m;
            invq[i] = invq[i-1]*invq[1];
            invq[i] %= m;
        }
    }
    array <int, 2> compute_hash(string s){
        prefhash[0] = {0, 0};
        for(int i = 0;i < s.size();i++){
            prefhash[i+1][0] = prefhash[i][0] + potp[i]*(s[i]-'a'+1);
            prefhash[i+1][0] %= m;
            prefhash[i+1][1] = prefhash[i][1] + potq[i]*(s[i]-'a'+1);
            prefhash[i+1][1] %= m;
        }
        return prefhash[s.size()];
    }
    array <int, 2> substring_hash(int i, int j){
        i++;
        j++;
        array <int, 2> res = {prefhash[j][0]-prefhash[i-1][0], prefhash[j][1]-prefhash[i-1][1]};
        res[0] %= m;
        res[0] += m;
        res[0] %= m;
        res[1] %= m;
        res[1] += m;
        res[1] %= m;
        res[0] *= invp[i-1];
        res[0] %= m;
        res[1] *= invq[i-1];
        res[1] %= m;
        return res;
    }
};
