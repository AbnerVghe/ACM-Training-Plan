#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

const int N = 110;
int dp[N][N];

bool check(char A, char B){
    int C = A, D = B;
    return (C == '(' && D == ')') || (C == '[' && D == ']');
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	//cout << check(']','[') << check(')','(') << check('[',')');
    //cout << (int)'(' << ' ' << (int)')' << ' ' << (int)'[' << ' ' << (int)']';

    string s;
    cin >> s;
    int n = s.length();
    foreach(0, n-1, i) dp[i][i] = 1;
    foreach(0, n-2, i) dp[i][i+1] = check(s[i], s[i+1]) ? 0 : 2;
    foreach_sub(n-3, 0, i){
        foreach(i+2, n-1, j){
            int ans = INF;
            if(check(s[i], s[j])) ans = dp[i+1][j-1];
            foreach(i, j-1, k){
                ans = min(ans, dp[i][k]+dp[k+1][j]);
            }
            dp[i][j] = ans;
        }
    }
    cout << dp[0][n-1];
}