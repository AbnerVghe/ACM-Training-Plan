#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        int prepare = -prices[0] - fee;
        int done = 0;
        foreach(1, n-1, i){
            done = max(done, prepare + prices[i]);
            prepare = max(prepare, done - prices[i] - fee);
        }
        return done;
    }
};