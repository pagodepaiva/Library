#include<bits/stdc++.h>
#define int long long
#define ms(v) memset(v, -1, sizeof v)
#define pb push_back
#define mp make_pair
#define ll long long int
#define pi pair <int,int>
#define itn int
#define fr first
#define sc second
#define srt(v) sort(v.begin(), v.end())
#define rvs(v) reverse(v.begin(), v.end())
#define mod 1000000007
#define INF 1e18
#define N 21

using namespace std;

int n;
int v[N][N];
int dp[N][(1 << N)];

int solve(int i, int mask){
    if(i == n and mask == (1 << n) - 1) return 1;
    if(dp[i][mask] != -1) return dp[i][mask];

    dp[i][mask] = 0;

    for(int j = 0;j < n;j++){
        if(!((1 << j) & mask) and v[i][j] == 1){
            dp[i][mask] += (solve(i+1, ((1 << j) | mask))) % mod;
        }
    }   

    dp[i][mask] %= mod;

    return dp[i][mask];
}

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);
    
    cin >> n;

    for(int i = 0;i< n;i++){
        for(int j = 0;j < n;j++){
            cin >> v[i][j];
        }
    }

    ms(dp);
    solve(0, 0);

    cout << dp[0][0] << "\n";

    return 0;
}
