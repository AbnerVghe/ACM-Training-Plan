#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 25;
bool dp[N][N]; 

class Solution {
public:
    bool isMatch(string s, string p) {
        int n = s.length(), m = p.length();
        memset(dp, 0, sizeof dp);
        dp[n][m] = 1;
        foreach_sub(m-2, 0, i){
            dp[n][i] = dp[n][i+2] & (p[i+1]=='*');
        }
        foreach_sub(n-1, 0, i){
            foreach_sub(m-1, 0, j){
                if(j+1<m && p[j+1]=='*'){
                    dp[i][j] |= dp[i][j+2];
                    if(s[i] == p[j] || p[j] == '.') dp[i][j] |= dp[i+1][j];
                }
                else{
                    if(s[i] == p[j] || p[j] == '.') dp[i][j] |= dp[i+1][j+1];
                }
            }
        }
        return dp[0][0];
    }
};