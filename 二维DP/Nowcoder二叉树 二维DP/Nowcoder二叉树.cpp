#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;
const int MOD = 1e9+7;

int dp[60][60];

signed main(){
    int n, m;
    cin >> n >> m;
    foreach(0, m, i) dp[0][i] = 1;
    foreach(1, n, i) dp[i][0] = 0;
    foreach(1, m, j){
        foreach(1, n, i){
            foreach(0, i-1, k){
                dp[i][j] = ((dp[k][j-1] * dp[i-1-k][j-1])%MOD + dp[i][j])%MOD;
            }
        }
    }
    cout << dp[n][m];

}