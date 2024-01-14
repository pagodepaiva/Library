string sum(string a, string b){
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    if(a.size() > b.size()) swap(a, b);
    while(a.size() < b.size()) a.push_back('0');
    int nx = 0;
    string res;
    for(int i = 0;i < a.size();i++){
        int t = nx + a[i] - '0' + b[i] - '0';
        if(t >= 10){
            nx = 1;
            t %= 10;
        }
        else {
            nx = 0;
        }
        res.push_back(t+'0');
    }
    if(nx == 1) res.push_back('1');
    reverse(res.begin(), res.end());
    return res;
}
