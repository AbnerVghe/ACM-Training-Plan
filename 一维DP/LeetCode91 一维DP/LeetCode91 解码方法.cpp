#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 110;

int n;
int f[N];

/*int dfs(int i, string s){
    if(i >= n) return 1;
    if(f[i] != INF) return f[i];

    int ans;
    if(s[i] == '0') ans = 0;
    else{
        ans = dfs(i+1, s);
        if(i+1 < n && (s[i]-'0')*10 + (s[i+1]-'0') <= 26){
            ans += dfs(i+2, s);
        }
    }
    f[i] = ans;
    return ans;
}*/

class Solution {
public:
    int numDecodings(string s) {
        n = s.length();
        foreach(0, n, i) f[i] = INF;
        //return dfs(0, s);
        f[n] = 1;
        foreach_sub(n-1, 0, i){
            if(s[i] == '0') f[i] = 0;
            else{
                f[i] = f[i+1];
                if(i+1 < n && (s[i]-'0')*10 + (s[i+1]-'0') <= 26){
                    f[i] += f[i+2];
                }
            }
        }
        return f[0];
    }
};

signed main(){
    Solution slu;
    string s = "226";
    cout << slu.numDecodings(s);
}