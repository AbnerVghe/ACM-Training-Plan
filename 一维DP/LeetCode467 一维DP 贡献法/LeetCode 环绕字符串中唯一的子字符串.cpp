#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

int dp[30];//from 'a' to 'z'

class Solution {
public:
    int findSubstringInWraproundString(string s) {
        int n = s.length();
        foreach(0, 25, i) dp[i] = 0;
        dp[s[0]-'a'] = 1;
        int cur = 1;
        foreach(1, n-1, i){
            if((s[i]!='a' && s[i]-s[i-1]==1) || (s[i]=='a' && s[i-1]=='z')){
                cur++;
            }
            else cur = 1;
            dp[s[i]-'a'] = max(dp[s[i]-'a'], cur);
        }
        int ans = 0;
        foreach(0, 25, i) ans += dp[i];
        return ans;
    }
};

signed main(){
    string s = "zip";
    Solution slu;
    cout << slu.findSubstringInWraproundString(s);
}