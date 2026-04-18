#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 1010;
int n;
int dp[N], best[N];

class Solution {
public:
    int free(vector<int>& prices){
        int ans = 0;
        foreach(0, n-2, i){
            if(prices[i] < prices[i+1]) ans += prices[i+1] - prices[i];
        }
        return ans;
    }

    int maxProfit(int k, vector<int>& prices) {
        n = prices.size();
        if(k >= n/2) return free(prices);

        foreach(0, n-1, i) dp[i] = 0;
        foreach(1, k, i){
            int best = -prices[0];
            foreach(1, n-1, j){
                int nextBest = max(best, dp[j]-prices[j]);
                dp[j] = max(dp[j-1], best+prices[j]);
                best = nextBest;
            }
        }
        return dp[n-1];
    }
};