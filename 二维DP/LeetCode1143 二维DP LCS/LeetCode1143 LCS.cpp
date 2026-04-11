#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 1010;
int dp[N][N];
int f[N];

class Solution1{
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n = text1.length(), m = text2.length();//i,j indicate the length of the substring
        foreach(0, n, i) dp[i][0] = 0;
        foreach(0, m, i) dp[0][i] = 0;
        foreach(1, n, i) foreach(1, m, j){
            if(text1[i-1]==text2[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
            else dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
        }
        return dp[n][m];
    }
};

class Solution{//memory reduce
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n = text1.length(), m = text2.length();
        foreach(0, m, i) f[i] = 0;
        foreach(1, n, i){
            int leftup = 0, backup;
            foreach(1, m, j){
                backup = f[j];
                if(text1[i-1] == text2[j-1]) f[j] = leftup + 1;
                else f[j] = max(f[j], f[j-1]);
                leftup = backup;
            }
        }
        return f[m];
    }
};

signed main(){
    Solution slu;
    string a = "abcd", b = "acbced";
    cout << slu.longestCommonSubsequence(a, b);
}