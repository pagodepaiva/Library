#include<bits/stdc++.h>

using namespace std;

const int N = 20;
int dp[(1<<N)][N];
int dp2[(1<<N)][N];
int val[(1<<N)];
int val2[(1<<N)];
int v[200010];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    int n;
    cin >> n;
    for(int i = 1;i <= n;i++){
        int x;
        cin >> x;
        val[x]++;
        val2[(((1<<N)-1)^x)]++;
        v[i] = x;
    }
    for(int i = 0;i < N;i++){
        for(int mask = 0;mask < (1<<N);mask++){
            if(i == 0){
                if((mask&1)){
                    dp[mask][i] = val[mask] + val[mask^1];
                    dp2[mask][i] = val2[mask] + val2[mask^1];
                }
                else{
                    dp[mask][i] = val[mask];
                    dp2[mask][i] = val2[mask];
                }
            }
            else{
                if((mask&(1<<i))){
                    dp[mask][i] = dp[mask][i-1] + dp[mask^(1<<i)][i-1];
                    dp2[mask][i] = dp2[mask][i-1] + dp2[mask^(1<<i)][i-1];
                }
                else{
                    dp[mask][i] = dp[mask][i-1];
                    dp2[mask][i] = dp2[mask][i-1];
                }
            }
        }
    }
    for(int i = 1;i <= n;i++){
        cout << dp[v[i]][N-1] << ' ' << dp2[(((1<<N)-1)^v[i])][N-1] << ' ' << n - dp[(((1<<N)-1)^v[i])][N-1] << '\n';
    }
}
