#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

typedef pair<int, int> pii;

const int N = 110;
int w[N], v[N];
int dp[1010];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	int T, n;
	cin >> T >> n;
	foreach(1, n, i){
		cin >> w[i] >> v[i];
	}
	foreach(1, n, i) foreach_sub(T, w[i], j){
		dp[j] = max(dp[j], dp[j-w[i]]+v[i]);
	}
	cout << dp[T];
}