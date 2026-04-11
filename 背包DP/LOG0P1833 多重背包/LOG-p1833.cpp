#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

const int N = 1e7+7, M = 1010;
int dp[M];
int w[N], v[N];

int compute(string A){
	int idx = 0;
	int hour = 0, minute = 0;
	while(A[idx] != ':'){
		hour *= 10;
		hour += A[idx++] - '0';
	}
	idx++;
	while(idx < A.length()){
		minute *= 10;
		minute += A[idx++] - '0';
	}
	return hour * 60 + minute;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	string A, B;
	cin >> A >> B;
	int m = compute(B) - compute(A);
	int n, tn = 0;
	cin >> n;
	foreach(1, n, i){
		int weight, val, cnt;
		cin >> weight >> val >> cnt;
		if(!cnt) cnt = m;
		
		for(int k = 1; k <= cnt; k <<= 1){
			w[++tn] = k * weight;
			v[tn] = k * val;
			cnt -= k;
		}
		if(cnt > 0){
			w[++tn] = cnt * weight;
			v[tn] = cnt * val;
		}
	}

	foreach(1, tn, i){
		foreach_sub(m, w[i], j){
			dp[j] = max(dp[j], dp[j-w[i]]+v[i]);
		}
	}
	cout << dp[m];
}