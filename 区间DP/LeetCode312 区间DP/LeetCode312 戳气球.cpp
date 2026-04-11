#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

const int N = 310;
int dp[N][N];
int arr[N];

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        arr[0] = arr[n+1] = 1;
        foreach(1, n, i) arr[i] = nums[i-1];
        foreach(1, n, i) dp[i][i] = arr[i-1] * arr[i] * arr[i+1];
        foreach_sub(n-1, 1, i){
            foreach(i+1, n, j){
                int p1 = arr[i-1] * arr[i] * arr[j+1] + dp[i+1][j];
                int p2 = arr[i-1] * arr[j] * arr[j+1] + dp[i][j-1];
                int ans = max(p1, p2);
                foreach(i+1, j-1, k){
                    ans = max(ans, arr[k] * arr[i-1] * arr[j+1] + dp[i][k-1] + dp[k+1][j]);
                }
                dp[i][j] = ans;
            }
        }
        return dp[1][n];
    }
};