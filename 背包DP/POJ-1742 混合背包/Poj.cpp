#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

const int N = 110, M = 1e5+7;
int w[N], c[N];
bool dp[M];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	while(1){
		int n, m;
		cin >> n >> m;
		if(!n && !m) break;

		foreach(1, n, i) cin >> w[i];
		foreach(1, n, i) cin >> c[i];
		foreach(1, m, i) dp[i] = 0;
		dp[0] = 1;

		foreach(1, n, i){
			if(c[i]==1){//01
				foreach_sub(m, w[i], j){
					dp[j] |= dp[j-w[i]];
				}
			}
			else if(c[i]*w[i] >= m){//完全
				foreach(w[i], m, j){
					dp[j] |= dp[j-w[i]];
				}
			}
			else{//多重
				for(int mod = 0; mod <= w[i]-1; mod++){
					int trueCnt = 0;
					for(int j = m-mod, cnt = 1; j >= 0 && cnt <= c[i]; j -= w[i], cnt++){
						trueCnt += dp[j];
					}
					for(int j = m-mod, enter = j - w[i]*c[i]; j >= 1; j -= w[i], enter -= w[i]){
						if(enter >= 0) trueCnt += dp[enter];
						bool past = dp[j];
						if(trueCnt > 0) dp[j] = 1;
						trueCnt -= past;
					}
				}
			}
		}

		int ans = 0;
		foreach(1, m, i){
			ans += dp[i];
		}
		cout << ans << '\n';
	}
}