#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 1e5+7;
int dp1[N], best[N];

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int minn = prices[0];
        int ans = 0;
        dp1[0] = best[0] = -prices[0];
        foreach(1, n, i){
            minn = min(minn, prices[i-1]);
            dp1[i] = max(dp1[i-1], prices[i-1]-minn);
            best[i] = max(best[i-1], dp1[i]-prices[i-1]);
            ans = max(ans, best[i-1]+prices[i-1]);
        }
        return ans;
    }
};