#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 1e4+7, M = 1e7+7;
int dp[M];
int w[N], v[N];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	int n, m;
	cin >> m >> n; 
	foreach(1, n, i){
		cin >> w[i] >> v[i];
	}
	foreach(1, n, i){
		foreach(w[i], m, j){
			dp[j] = max(dp[j], dp[j-w[i]]+v[i]);
		}
	}
	cout << dp[m];
}