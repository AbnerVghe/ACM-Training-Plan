#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

int dp[3010];

class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int n = stones.size();
        int sum = 0;
        for(auto stone: stones) sum += stone;

        foreach(0, sum, i) dp[i] = 0;
        for(auto stone: stones){
            foreach_sub(sum/2, stone, i){
                dp[i] = max(dp[i], dp[i-stone]+stone);
            }
        }
        int near = dp[sum/2];
        return sum - 2*near;
    }
};