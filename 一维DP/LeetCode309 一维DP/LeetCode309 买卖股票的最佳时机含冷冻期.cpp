#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 5010;
int prepare[N], done[N];
//prepare: 到i，无限制购买并减去一次购买费用的最好情况
//done: 到i，无限制购买的最好情况
//以上均考虑冷静期

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();     
        if(n < 2) return 0;

        prepare[0] = -prices[0];
        done[0] = 0;
        prepare[1] = max(-prices[0], -prices[1]);
        done[1] = max(0, prices[1]-prices[0]);
        foreach(2, n-1, i){
            done[i] = max(done[i-1], prepare[i-1]+prices[i]);
            prepare[i] = max(prepare[i-1], done[i-2]-prices[i]);
        }
        return done[n-1];
    }
};