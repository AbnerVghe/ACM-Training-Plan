#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int MOD = 1e9+7;

class Solution {
public:
    int numberOfPaths(vector<vector<int>>& grid, int k) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(m+1, vector<int>(k, 0)));
        
        dp[n-1][m-1][grid[n-1][m-1] % k] = 1;
        foreach_sub(n-2, 0, i) foreach(0, k-1, r) dp[i][m-1][r] = (dp[i+1][m-1][(k+r-grid[i][m-1]%k)%k])%MOD;
        foreach_sub(m-2, 0, i) foreach(0, k-1, r) dp[n-1][i][r] = (dp[n-1][i+1][(k+r-grid[n-1][i]%k)%k])%MOD;

        foreach_sub(n-2, 0, i) foreach_sub(m-2, 0, j) foreach(0, k-1, r){
            int need = (k+r-grid[i][j]%k)%k;
            dp[i][j][r] = (dp[i+1][j][need] + dp[i][j+1][need])%MOD;
        }

        return dp[0][0][0];
    }
};

signed main(){
    Solution slu;
}