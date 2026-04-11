#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

const int N = 110, M = 4e4+7;
int w[N], v[N], c[N]; 
int dp[M];
int q[M];

int value(int i, int j){
	return dp[j] - (j / w[i]) * v[i];
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	int n, m;
	cin >> n >> m;
	foreach(1, n, i){
		cin >> v[i] >> w[i] >> c[i];
	}

	foreach(1, n, i){
		for(int mod = 0; mod <= min(w[i]-1, m); mod++){
			//建立单调窗口
			int l, r;
			l = r = 0;
			for(int j = m - mod, cnt = 1; j >= 0 && cnt <= c[i]; j -= w[i], cnt++){
				while(l < r && value(i, q[r-1]) <= value(i, j)) r--;
				q[r++] = j;
			}
			for(int j = m - mod, enter = j - w[i] * c[i]; j >= 0; j -= w[i], enter -= w[i]){
				//enter位置紧急置入
				if(enter >= 0){
					while(l < r && value(i, q[r-1]) <= value(i, enter)) r--;
					q[r++] = enter;
				}
				dp[j] = value(i, q[l]) + (j / w[i]) * v[i];
				//弹出当前j处指标
				if(q[l] == j) l++;
			}
		}
	}

	cout << dp[m];
}