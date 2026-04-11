#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF LONG_LONG_MAX

typedef pair<int, int> pii;

const int N = 5e5+7;
int n, m;
ll l, r;
int a[20];
ll dis[N];

void circle(){
	foreach(0, m-1, i){
		dis[i] = INF;
	}

	dis[0] = 0;
	foreach(1, n, i){
		if(a[i] == m) continue;

		int d = __gcd(a[i], m);
		foreach(0, d-1, j){
			for(int x = j, c = 1; c <= 2; c += (x == j)){
				int y = (x+a[i]) % m;
				if(dis[x]+a[i]<0) continue;
				dis[y] = min(dis[y], dis[x]+a[i]);
				x = y;
			}
		}
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> n >> l >> r;
	int cnt = 0;
	m = N;
	foreach(1, n, i){
		int tmp;
		cin >> tmp;
		if(tmp){
			a[++cnt] = tmp;
			m = min(m, tmp);
		}
	}
	n = cnt;
	//cout << cnt << '\n';

	circle();

	ll ans1 = 0, ans2 = 0;
	foreach(0, m-1, i){
		ans1 += (dis[i]<=r) ? (r-dis[i])/m + 1 : 0;
		ans2 += (dis[i]<=l-1) ? (l-1-dis[i])/m + 1 : 0;
	}
	cout << ans1 - ans2;
}