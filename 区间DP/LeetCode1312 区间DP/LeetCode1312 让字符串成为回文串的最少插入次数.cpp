#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 510;
int dp[N][N];

class Solution {
public:
    int minInsertions(string s) {
        int n = s.length();
        foreach(1, n, i) dp[i][i] = 0;
        foreach(1, n-1, i) dp[i][i+1] = (s[i-1] == s[i]) ? 0 : 1;
        foreach_sub(n-2, 1, i){
            foreach(i+2, n, j){
                if(s[i-1] == s[j-1]) dp[i][j] = dp[i+1][j-1];
                else dp[i][j] = min(dp[i+1][j], dp[i][j-1]) + 1;
            }
        }
        return dp[1][n];
    }
};