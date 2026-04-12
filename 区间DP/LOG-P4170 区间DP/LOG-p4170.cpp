#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

const int N = 60;
int dp[N][N];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	string s;
	cin >> s;
	int n = s.length();
	foreach(0, n-1, i) dp[i][i] = 1;
	foreach_sub(n-2, 0, i){
		foreach(i+1, n-1, j){
			if(s[i] == s[j]) dp[i][j] = dp[i+1][j];
			else{
				int ans = INF;
				foreach(i, j-1, k){
					ans = min(ans, dp[i][k]+dp[k+1][j]);
				}
				dp[i][j] = ans;
			}
		}
	}
	cout << dp[0][n-1];
}