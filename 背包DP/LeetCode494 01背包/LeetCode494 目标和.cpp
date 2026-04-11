#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 30;
int dp[20010];//前i个物品能凑出j的方案数

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size();
        int sum = 0;
        foreach(0, n-1, i) sum += nums[i];
        if((sum&1)!=(target&1) || sum < target) return 0;
        int sumA = (sum+target)/2;

        if(sumA < 0) return 0;
        foreach(1, sumA, i) dp[i] = 0;
        dp[0] = 1;
        for(auto num: nums){
            foreach_sub(sumA, num, j){
                dp[j] += dp[j-num];
            }
        }
        return dp[sumA];
    }
};