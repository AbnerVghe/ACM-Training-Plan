#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

const int N = 1010, MOD = 19650827;
int dp[N][N][2];
int a[N];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	int n;
	cin >> n;
	foreach(1, n, i){
		cin >> a[i];
	}
	foreach(1, n-1, i){
		if(a[i] < a[i+1]){
			dp[i][i+1][0] = dp[i][i+1][1] = 1;
		}
	}
	foreach_sub(n-2, 1, i){
		foreach(i+2, n, j){
			int ans0 = 0, ans1 = 0;
			if(a[i] < a[i+1]) ans0 = dp[i+1][j][0];
			if(a[i] < a[j]) ans0 = (ans0 + dp[i+1][j][1])%MOD;
			if(a[j] > a[i]) ans1 = dp[i][j-1][0];
			if(a[j] > a[j-1]) ans1 = (ans1 + dp[i][j-1][1])%MOD;
			dp[i][j][0] = ans0, dp[i][j][1] = ans1;
		}
	}
	cout << (dp[1][n][0] + dp[1][n][1])%MOD;
}