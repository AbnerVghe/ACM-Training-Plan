#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

int dp[40][40][40];
int dp2[40][40][40];
int n;

bool f(string s1, string s2, int l1, int l2, int len){
    if(len == 1) return s1[l1] == s2[l2];
    if(dp[l1][l2][len] != 0) return dp[l1][l2][len] == 1;
    bool ans = 0;
    for(int k = 1; k < len; k++){
        if(f(s1, s2, l1, l2, k) && f(s1, s2, l1+k, l2+k, len-k)){
            ans = 1;
            break;
        }
    }
    if(!ans){
        for(int i = l1+1, j = l2+len-1, k = 1; k < len; i++, j--, k++){
            if(f(s1, s2, l1, j, k) && f(s1, s2, i, l2, len - k)){
                ans = 1;
                break;
            }
        }
    }
    dp[l1][l2][len] = ans ? 1 : -1;
    return ans;
}

class Solution {
public:
    bool isScramble2(string s1, string s2) {
        n = s1.length();
        foreach(0, n, i) foreach(0, n, j) foreach(1, n, k) dp[i][j][k] = 0;
        return f(s1, s2, 0, 0, n);
    }

    bool isScramble(string s1, string s2){
        n = s1.length();
        foreach(0, n-1, i) foreach(0, n-1, j) foreach(2, n, k) dp2[i][j][k] = 0;
        foreach(0, n-1, i) foreach(0, n-1, j) dp2[i][j][1] = (s1[i] == s2[j]);
        foreach(2, n, len) foreach_sub(n-len, 0, i) foreach_sub(n-len, 0, j){
            bool ans = 0;
            foreach(1, len-1, k){
                //if(i+k>=n || j+k>=n) break;
                
                if(dp2[i][j][k] && dp2[i+k][j+k][len-k]){
                    ans = 1;
                    break;
                }
            }
            if(!ans){
                for(int ip = i+1, jp = j+len-1, k = 1; k < len; ip++, jp--, k++){
                    if(dp2[i][jp][k] && dp2[ip][j][len-k]){
                        ans = 1;
                        break;
                    }
                }
            }
            dp2[i][j][len] = ans;
        }
        return dp2[0][0][n];
    }
};