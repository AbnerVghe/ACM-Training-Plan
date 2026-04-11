#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

const int N = 110, M = 50010;
int dp[M+5000];
int w[N], v[N];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	int n, h;
	cin >> n >> h;
	int maxn = 0;
	foreach(1, n, i){
		cin >> w[i] >> v[i];
		maxn = max(maxn, w[i]);
	}
	memset(dp, INF, sizeof dp);
	dp[0] = 0;
	foreach(1, n, i){
		foreach(w[i], h+maxn, j){
			dp[j] = min(dp[j], dp[j-w[i]]+v[i]);
		}
	}
	int ans = INF;
	foreach(h, h+maxn, i){
		ans = min(ans, dp[i]);
	}
	cout << ans;
}