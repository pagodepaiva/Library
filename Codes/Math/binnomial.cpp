const int N = 2000010;
const long long mod = 1e9+7;
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

long long fact[N], inv_fact[N];

void prep(){
    fact[0] = 1;
    for(int i = 1;i < N;i++){
        fact[i] = fact[i-1]*i;
        fact[i] %= mod;
    }
    inv_fact[N-1] = binpow(fact[N-1], mod-2, mod);
    for(int i = N-2;i >= 0;i--){
        inv_fact[i] = inv_fact[i+1] * (i+1);
        inv_fact[i] %= mod;
    }
}

int choose(int a, int b){
    if(a < 0 or b > a or b < 0){
        return 0;
    }
    return (fact[a] * ((inv_fact[b] * inv_fact[a-b]) % mod)) % mod;
}
