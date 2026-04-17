#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 5010;
int dp[N][N];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string s1, s2;
    cin >> s1 >> s2;
    int n = s1.length(), m = s2.length();
    foreach(1, n, i) foreach(1, m, j){
        if(s1[i-1] == s2[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
        else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
    }
    //cout << dp[n][m];
    int len = dp[n][m];
    if(!len) cout << -1;
    else{
        int i = n, j = m;
        string s;
        while(len){
            if(s1[i-1] == s2[j-1]){
                s += s1[i-1];
                i--, j--;
                len--;
            }
            else{
                if(dp[i-1][j] >= dp[i][j-1]){
                    i--;
                }
                else j--;
            }
        }
        reverse(s.begin(), s.end());
        cout << s;
    }
}