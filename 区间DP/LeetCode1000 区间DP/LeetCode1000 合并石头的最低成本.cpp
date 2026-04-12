#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

const int N = 40;
int dp[N][N];
int pre[N];

class Solution {
public:
    int mergeStones(vector<int>& stones, int k) {
        int n = stones.size();
        if((n-1) % (k-1) != 0) return -1;

        pre[0] = 0;
        foreach(0, n-1, i){
            pre[i+1] = stones[i] + pre[i];
        }

        foreach(0, n-1, i) dp[i][i] = 0;

        foreach_sub(n-2, 0, i){
            foreach(i+1, n-1, j){
                int ans = INF;
                for(int m = i; m < j; m += k - 1){
                    ans = min(ans, dp[i][m] + dp[m+1][j]);
                }
                if((j-i) % (k-1) == 0) ans += pre[j+1] - pre[i];
                dp[i][j] = ans;
            }
        }

        return dp[0][n-1];
    }
};