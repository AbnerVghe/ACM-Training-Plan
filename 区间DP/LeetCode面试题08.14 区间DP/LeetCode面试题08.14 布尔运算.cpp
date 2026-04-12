#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

const int N = 50;
int dp[N][N][2];

class Solution {
public:
    int countEval(string s, int result) {
        int n = s.length();
        memset(dp, 0, sizeof dp);
        for(int i = 0; i < n; i += 2){
            dp[i][i][0] = (s[i] == '0') ? 1 : 0;
            dp[i][i][1] = (s[i] == '1') ? 1 : 0;
        }
        for(int i = n-3; i >= 0; i -= 2){
            for(int j = i+2; j <= n-1; j += 2){
                for(int k = i+1; k <= j-1; k += 2){
                    int l0 = dp[i][k-1][0], l1 = dp[i][k-1][1], r0 = dp[k+1][j][0], r1 = dp[k+1][j][1];
                    int ans0, ans1;
                    if(s[k] == '&'){
                        ans0 = l0 * r0 + l1 * r0 + l0 * r1;
                        ans1 = l1 * r1;
                    }
                    else if(s[k] == '|'){
                        ans0 = l0 * r0;
                        ans1 = l0 * r1 + l1 * r0 + l1 * r1;
                    }
                    else if(s[k] == '^'){
                        ans0 = l0 * r0 + l1 * r1;
                        ans1 = l0 * r1 + l1 * r0;
                    }
                    dp[i][j][0] += ans0, dp[i][j][1] += ans1;
                }
            }
        }
        return dp[0][n-1][result];
    }
};

signed main(){
    Solution slu;
    cout << slu.countEval("1^0|0|1", 0);
}