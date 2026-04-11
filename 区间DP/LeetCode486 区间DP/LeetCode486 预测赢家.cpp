#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 30;
int dp[N][N];

class Solution {
public:
    bool predictTheWinner(vector<int>& nums) {
        int n = nums.size();
        foreach(1, n, i) dp[i][i] = nums[i-1];
        foreach(1, n-1, i) dp[i][i+1] = max(nums[i-1], nums[i]);
        foreach_sub(n-2, 1, i){
            foreach(i+2, n, j){
                int p1 = nums[i-1] + min(dp[i+2][j], dp[i+1][j-1]);
                int p2 = nums[j-1] + min(dp[i][j-2], dp[i+1][j-1]);
                dp[i][j] = max(p1, p2);
            }
        }
        int player1 = dp[1][n];
        int sum = 0;
        for(auto num: nums) sum += num;
        int player2 = sum - player1;
        return player1 >= player2;
    }
};