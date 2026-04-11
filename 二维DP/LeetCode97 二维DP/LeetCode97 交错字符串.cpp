#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

int dp[110][210];

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if(s3.length() != s1.length()+s2.length()) return 0;
        
        int n = s1.length(), m = s1.length()+s2.length();
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        foreach(0, n, i){
            foreach(1, m, j){
                if(j-i>0 && j-i-1<m-n && s2[j-i-1] == s3[j-1]) dp[i][j] |= dp[i][j-1];
                if(i>0 && s1[i-1] == s3[j-1]) dp[i][j] |= dp[i-1][j-1];
            }
        }
        return dp[n][m];
    }
};

signed main(){
    Solution slu;
    string s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac";
    cout << slu.isInterleave(s1, s2, s3);
}