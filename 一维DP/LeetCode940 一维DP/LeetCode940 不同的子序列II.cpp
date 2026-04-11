#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
const int MOD = 1e9 + 7;
using namespace std;

int dp[30];
int all;

class Solution {
public:
    int distinctSubseqII(string s) {
        int n = s.length();
        all = 1;
        foreach(0, 25, i) dp[i] = 0;

        foreach(0, n-1, i){
            int newstr = (all - dp[s[i]-'a'] + MOD)%MOD;
            dp[s[i]-'a'] = (dp[s[i]-'a']+newstr)%MOD;
            all = (all+newstr)%MOD;
        }

        return (all-1+MOD)%MOD;
    }
};

signed main(){
    Solution slu;
    string s = "aaa";
    cout << slu.distinctSubseqII(s);
}