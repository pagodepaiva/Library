#include<bits/stdc++.h>
#define N 1010 

using namespace std;

int main(){    
    int n;
    cin >> n;
    int v[N], sum = 0;
    for(int i = 1;i <= n;i++){
        cin >> v[i];
        sum += v[i];
    }
    sum /= n;
    for(int i = 1;i <= n;i++){
        cout << sum - v[i] << "\n";
    }
    return 0;   
}
