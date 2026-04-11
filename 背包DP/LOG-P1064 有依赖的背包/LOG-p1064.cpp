#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

typedef pair<int, int> pii;

const int N = 70, M = 32010;
int v[N], w[N];
int dp[M];
bool king[N];
vector<int> fans[N];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	int m, n;
	cin >> m >> n;
	foreach(1, n, i){
		int price, p, q;
		cin >> price >> p >> q;
		v[i] = price;
		w[i] = price * p;
		if(!q) king[i] = 1; 
		else{
			fans[q].push_back(i);
			king[i] = 0;
		}
	}
	foreach(1, n, i){
		if(!king[i]) continue;
		int fnum = fans[i].size();
		foreach_sub(m, v[i], j){
			dp[j] = max(dp[j], dp[j-v[i]]+w[i]);
			
			if(fnum>=1){
			for(auto fan: fans[i]){
				if(j >= v[i]+v[fan]){
						dp[j] = max(dp[j], dp[j-v[i]-v[fan]]+w[i]+w[fan]);
					}
				}
			}

			if(fnum>=2){
				int fan1 = fans[i][0], fan2 = fans[i][1];
				if(j >= v[i]+v[fan1]+v[fan2]) dp[j] = max(dp[j], dp[j-v[i]-v[fan1]-v[fan2]]+w[i]+w[fan1]+w[fan2]);
			}
		}
		
	}
	//int ans = 0;
	//foreach(0, m, i) ans = max(ans, dp[i]);
	cout << dp[m];
}