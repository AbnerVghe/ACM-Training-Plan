#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 210;
int m, n;
int dp[N];

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        m = grid.size(), n = grid[0].size();
        dp[0] = grid[0][0];
        foreach(1, n-1, i) dp[i] = dp[i-1] + grid[0][i];
        foreach(1, m-1, i){
            dp[0] += grid[i][0];
            foreach(1, n-1, j){
                dp[j] = min(dp[j], dp[j-1]) + grid[i][j];
            }
        }
        return dp[n-1];
    }
};

signed main(){
    vector<vector<int>> grid = {{1,2,3},{4,5,6}};
    Solution slu;
    cout << slu.minPathSum(grid); 
}