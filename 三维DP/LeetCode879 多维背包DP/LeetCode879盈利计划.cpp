#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 110, MOD = 1e9+7;

int dp[N][N];

class Solution {
public:
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        foreach(0, n, i) dp[i][0] = 1;
        foreach(0, n, i) foreach(1, minProfit, j) dp[i][j] = 0;

        foreach(0, group.size()-1, i){
            foreach_sub(n, group[i], j){
                foreach_sub(minProfit, 0, k){
                    dp[j][k] = (dp[j][k] + dp[j-group[i]][max(0, k-profit[i])])%MOD;
                }
            }
        }

        return dp[n][minProfit];
    }
};

signed main(){
    Solution slu;

}