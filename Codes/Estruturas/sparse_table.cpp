for(int bit = 1;bit < LOGN;bit++){
        int j = bit;
        for(int i = 1;i <= n;i++){
            st[i][j] = min(st[i][j-1], st[i + (1 << (bit-1))][j-1]);
        }
    }
    while(q--){
        int a, b;
        cin >> a >> b;
        int l = log2_floor(b-a+1);
        cout << min(st[a][l], st[b - (1 << l) + 1][l]) << '\n';
    }
