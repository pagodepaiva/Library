struct Substring_hash{
    /*
    Detalhes:
    - Escolha o primo que for usar. Deixei uma lista de 10 primos por padrao
    - Alem de retornar o hash de uma string, esse struct retorna a substring_hash de uma string.
    - O struct espera que so usamos letras minusculas
    - O struct espera que as perguntas de substring sejam 0 indexadas
    */
    vector <int> primos = {467, 733, 907, 937, 383, 607, 457, 107, 353, 577};
    const long long m = 36893401;
    long long pot[tam_hash], inv_pot[tam_hash];
    long long pref[tam_hash];
    long long p;
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
    void build(int c){
        p = primos[c];
        pot[0] = 1;
        inv_pot[1] = binpow(p, m-2, m);
        inv_pot[0] = 1;
        for(int i = 1;i < tam_hash;i++){
            pot[i] = (pot[i-1]*p) % m;
            if(i == 1)
                continue;
            inv_pot[i] = (inv_pot[i-1]*inv_pot[1]) % m;
        }
    }
    long long compute_hash(string &s){
        pref[0] = 0;
        for(int i = 0;i < s.size();i++){
            pref[i+1] = (pref[i] + pot[i]*(((long long) s[i] - 'a' + 1))) % m;
        }
        return pref[s.size()];
    }
    long long substring_hash(int i, int j){
        i++;
        j++;
        long long res = ((pref[j] - pref[i-1]) % m + m)%m;
        res *= inv_pot[i-1];
        res %= m;
        return res;
    }
};

struct Merge_hash{
    Substring_hash h1, h2;
    pair <int, int> compute_hash(string &s){
        h1.build(0);
        h2.build(1);
        return {h1.compute_hash(s), h2.compute_hash(s)};
    }
    pair <int, int> substring_hash(int i, int j){
        return {h1.substring_hash(i, j), h2.substring_hash(i, j)};
    }
};

struct Palindrome_check{
    Merge_hash h, inv_h;
    int n;
    void compute_hash(string &s){
        n = s.size();
        h.compute_hash(s);
        reverse(s.begin(), s.end());
        inv_h.compute_hash(s);
        reverse(s.begin(), s.end());
        return;        
    }
    bool is_palindrome(int i, int j){
        if(h.substring_hash(i, j) == inv_h.substring_hash(n-1-j, n-1-i))
            return true;
        return false;
    }
} h;
