#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

const int N = 80;
int dp[N][N];

class Solution {
public:
    int minScoreTriangulation(vector<int>& values) {
        int n = values.size();
        //foreach(0, n-1, i) dp[i][i] = 0;
        foreach(0, n-2, i) dp[i][i+1] = 0;
        foreach_sub(n-3, 0, i){
            foreach(i+2, n-1, j){
                int ans = INF;
                foreach(i+1, j-1, k){
                    ans = min(ans, dp[i][k]+dp[k][j]+values[i]*values[j]*values[k]);
                }
                dp[i][j] = ans;
            }
        }
        return dp[0][n-1];
    }
};