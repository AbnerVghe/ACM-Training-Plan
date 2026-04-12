#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f


const int N = 1010, mod = 1e9+7;
ll dp[N][N];
int last[N], Left[N], Right[N];

class Solution {
public:
    int countPalindromicSubsequences(string s) {
        int n = s.size();
        foreach(0, n-1, i) last[i] = -1;
        foreach(0, n-1, i){
            Left[i] = last[s[i]];
            last[s[i]] = i;
        }
        foreach(0, n-1, i) last[i] = n;
        foreach_sub(n-1, 0, i){
            Right[i] = last[s[i]];
            last[s[i]] = i;
        }

        foreach(0, n-1, i) foreach(0, n-1, j) dp[i][j] = 0;
        foreach(0, n-1, i) dp[i][i] = 1;
        foreach_sub(n-2, 0, i){
            foreach(i+1, n-1, j){
                if(s[i] != s[j]){
                    dp[i][j] = dp[i][j-1] + dp[i+1][j] - dp[i+1][j-1] + mod;
                }
                else{
                    int l = Right[i], r = Left[j];
                    if(l > r) dp[i][j] = dp[i+1][j-1] * 2 + 2;
                    else if(l == r){
                        dp[i][j] = dp[i+1][j-1] * 2 + 1;
                    }
                    else{
                        dp[i][j] = dp[i+1][j-1] * 2 - dp[l+1][r-1] + mod;
                    }
                }
                dp[i][j] %= mod;
            }
        }

        return dp[0][n-1];
    }
};