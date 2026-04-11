#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

const int N = 110;
int dp[N][N];
int arr[N];

class Solution {
public:
    int minCost(int n, vector<int>& cuts) {
        int m = cuts.size();
        sort(cuts.begin(), cuts.end());
        memset(dp, 0, sizeof dp);
        arr[0] = 0;
        foreach(1, m, i) arr[i] = cuts[i-1];
        arr[m+1] = n;

        foreach(1, m, i) dp[i][i] = arr[i+1] - arr[i-1];
        foreach_sub(m-1, 1, i){
            foreach(i+1, m, j){
                int ans = INF;
                foreach(i, j, k){
                    ans = min(ans, dp[i][k-1]+dp[k+1][j]+arr[j+1]-arr[i-1]);
                }
                dp[i][j] = ans;
            }
        }
        return dp[1][m];
    }
};