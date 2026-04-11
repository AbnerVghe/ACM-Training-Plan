#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 1010;
int dp[N][N];

class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.length();
        foreach_sub(n-1, 0, i){
            dp[i][i] = 1;
            if(i+1 < n){
                dp[i][i+1] = (s[i] == s[i+1]) ? 2 : 1;
            }
            foreach(i+2, n-1, j){
                if(s[i] == s[j]) dp[i][j] = dp[i+1][j-1] + 2;
                else dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
            }
        }
        return dp[0][n-1];
    }
};

signed main(){
    string s = "cbbd";
    Solution slu;
    cout << slu.longestPalindromeSubseq(s);
}