vector <int> prefix_function(string s){
    vector <int> p(s.size(), 0);
    p[0] = 0;
    for(int i = 1;i < s.size();i++){
        int j = p[i-1];
        while(j > 0 and s[i] != s[j])
            j = p[j-1];
        if(s[i] == s[j])
            j++;
        p[i] = j;
    }
    return p;
}
