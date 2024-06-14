for(int i = 1;i < kmp.size();i++){
        int j = p[i-1];
        while(j > 0 and kmp[i] != kmp[j])
            j = p[j-1];
        if(kmp[i] == kmp[j])
            j++;
        p[i] = j;
    }
