// INCOMPLETO

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

int rest(int a, int b){
    return ((a % b) + b) % b;
}


pair <int, int> equation(int a, int b, int c){
    // acha as solucoes da equacao ax+by = c
    if(a < 0){
        a *= -1;
        b *= -1;
        c *= -1;
    }
    if(a == 0){
        return {1, 0};
    }
    int g = gcd(abs(a), abs(b));
    a /= g;
    b /= g;
    c /= g;
    int inv = ((rest(c, a))*(binpow(b, a-2, a))) % a;
    return {a, inv};
}


int points_in_segment(pt a, pt b){
    // calcula quantos pontos tem na reta ab
    int l = min(a.y, b.y), r = max(a.y, b.y);
    line ll(a, b);
    int b_linha = ll.v.x, a_linha = -ll.v.y, c_linha = ll.c;
    if(b_linha == 0){
        return r-l+1;
    }
    else if(a_linha == 0){
        return max(a.x, b.x) - min(a.x, b.x) + 1;
    }
    auto [mod, resto] = equation(a_linha, b_linha, c_linha);
   // cout << mod << '\n';
    if(rest(l, mod) <= resto){
        l += (resto - (rest(l,mod)));
    }
    else{
        l += ((mod - (rest(l, mod))) + resto);
    }
    if(rest(r, mod) >= resto){
        r -= (rest(r,mod)) - resto;
    }
    else{
        r -= (rest(r, mod)) + (mod - resto);
    }
    //cout << l << ' ' << r << '\n';
    if(l < 0) {
        l -= mod-1;
    }
    l /= mod;
    if(r < 0){
        r -= mod-1;
    }    
    r /= mod;
    return r-l+1;
}   

int pick(vector <pt> v){
    // calcula quantos lattice points estao no poligono usando teorema de pick
    int b = 0;
    for(int i = 0, n = v.size();i < v.size();i++){
        //cout << points_in_segment(v[i], v[(i+1)%n]) << '\n';
        b += points_in_segment(v[i], v[(i+1)%n])-1;
    } 
    int area = area_polygon(v);
    int I = (area-b+2)/2;
    cout << I << ' ' << b << '\n';
    return I;
}

void solve(){
    vector <pt> v;
    int n;
    cin >> n;
    for(int i = 1;i <= n;i++){
        pt x;
        cin >> x;
        x.x += 1e9;
        x.y += 1e9;
        v.push_back(x);
    }
    pick(v);
}
