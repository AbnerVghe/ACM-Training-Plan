#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int MOD = 1e9+7;
int dp[210][210];

class Solution {
public:
    int numPermsDISequence(string s) {
        int n = s.length()+1;
        foreach(0, n-1, i) foreach(0, n, j) dp[i][j] = 0;
        foreach(0, n, i) dp[n][i] = 1;
        foreach_sub(n-1, 0, i){
            if(!i || s[i-1] == 'D'){
                dp[i][1] = dp[i+1][0];
                foreach(2, n, j){
                    dp[i][j] = (dp[i+1][j-1] + dp[i][j-1]) % MOD;
                }
            }
            else{
                dp[i][n-i-1] = dp[i+1][n-i-1];
                foreach_sub(n-i-2, 0, j){
                    dp[i][j] = (dp[i+1][j] + dp[i][j+1]) % MOD;
                }
            }
        }
        return dp[0][n];
    }
};