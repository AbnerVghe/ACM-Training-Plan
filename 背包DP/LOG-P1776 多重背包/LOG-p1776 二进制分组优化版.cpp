#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

const int N = 1e5, M = 4e4+7;
int w[N], v[N];
int dp[M];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	int t, W, n = 0;
	cin >> t >> W;
	foreach(1, t, i){
		int cnt, weight, val;
		cin >> val >> weight >> cnt;
		for(int k = 1; k <= cnt; k <<= 1){
			w[++n] = weight * k;
			v[n] = val * k;
			cnt -= k;
		}
		if(cnt > 0){
			w[++n] = weight * cnt;
			v[n] = val * cnt;
		}
	}
	foreach(1, n, i){
		foreach_sub(W, w[i], j){
			dp[j] = max(dp[j], dp[j-w[i]]+v[i]);
		}
	}
	cout << dp[W];
}