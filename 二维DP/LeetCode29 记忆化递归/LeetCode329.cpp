#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

int m, n;
int dp[210][210];

int dfs(int i, int j, vector<vector<int>> &matrix){
    if(dp[i][j]) return dp[i][j];
    int next = 0;
    
    if(i > 0 && matrix[i][j] < matrix[i-1][j]){
        next = max(next, dfs(i-1, j, matrix));
    }
    if(i+1 < m && matrix[i][j] < matrix[i+1][j]){
        next = max(next, dfs(i+1, j, matrix));
    }
    if(j > 0 && matrix[i][j] < matrix[i][j-1]){
        next = max(next, dfs(i, j-1, matrix));
    }
    if(j+1 < n && matrix[i][j] < matrix[i][j+1]){
        next = max(next, dfs(i, j+1, matrix));
    }
    dp[i][j] = next+1;
    return next+1;
}

class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        m = matrix.size(), n = matrix[0].size();
        foreach(0, m-1, i) foreach(0, n-1, j) dp[i][j] = 0;
        int ans = 1;
        foreach(0, m-1, i) foreach(0, n-1, j){
            ans = max(ans, dfs(i, j, matrix));
        }   
        return ans;
    }
};

signed main(){
    Solution slu;
    vector<vector<int>> matrix = {{9,9,4},{6,6,8},{2,1,1}};
    cout << slu.longestIncreasingPath(matrix);
}