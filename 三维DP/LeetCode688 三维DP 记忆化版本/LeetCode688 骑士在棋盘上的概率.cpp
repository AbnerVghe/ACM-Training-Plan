#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 30, K = 110;
double dp[N][N][K];//dp[i][j][k]:在(i,j)并且还有k步存活的概率

double f(int n, int k, int i, int j){
    if(i<0 || j<0 || i>=n || j>=n) return 0;
    if(dp[i][j][k] != -1) return dp[i][j][k];
    double ans = 0;
    if(!k) ans = 1;
    else{
        ans += f(n, k-1, i-1, j-2) / 8;
        ans += f(n, k-1, i-2, j-1) / 8;
        ans += f(n, k-1, i-1, j+2) / 8;
        ans += f(n, k-1, i-2, j+1) / 8;
        ans += f(n, k-1, i+1, j-2) / 8;
        ans += f(n, k-1, i+2, j-1) / 8;
        ans += f(n, k-1, i+1, j+2) / 8;
        ans += f(n, k-1, i+2, j+1) / 8;
    }
    dp[i][j][k] = ans;
    return ans;
}

class Solution {
public:
    double knightProbability(int n, int k, int row, int column) {
        foreach(0, n-1, i) foreach(0, n-1, j) foreach(0, k, p) dp[i][j][p] = -1;
        return f(n, k, row, column);
    }
};

signed main(){
    Solution slu;
    int n = 3, k = 2, row = 0, column = 0;
    cout << slu.knightProbability(n, k, row, column);
}