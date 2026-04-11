#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 2010;
bool dp[N][N];

class Solution {
public:
    bool isMatch(string s, string p) {
        int n = s.length(), m = p.length();
        foreach(0, n, i) foreach(0, m, j) dp[i][j] = 0;
        dp[n][m] = 1;
        foreach_sub(m-1, 0, i) dp[n][i] |= (p[i] == '*') & dp[n][i+1];
        foreach_sub(n-1, 0, i){
            foreach_sub(m-1, 0, j){
                if(p[j] == '*'){
                    dp[i][j] |= dp[i][j+1] | dp[i+1][j];
                }
                else{
                    dp[i][j] |= (s[i] == p[j] || p[j] == '?') & dp[i+1][j+1];
                }
            }
        }
        return dp[0][0];
     }
};