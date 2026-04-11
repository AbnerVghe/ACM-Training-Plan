#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 3e4+7;
int dp[N];

class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.length(), ans = 0;
        foreach(0, n, i) dp[i] = 0;
        dp[0] = 0;
        foreach(1, n-1, i){
            if(s[i] == '(') dp[i] = 0;
            else{
                int pre = dp[i-1];
                if(i-pre>0 && s[i-pre-1] == '('){
                    dp[i] = 2 + pre;
                    if(i-pre-1>0) dp[i] += dp[i-pre-2];
                }
                ans = max(ans, dp[i]);
            }
        }
        return ans;
    }
};

signed main(){
    Solution slu;
    string s = ")()())()()(";
    cout << slu.longestValidParentheses(s);
}