#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF LONG_LONG_MAX

typedef pair<int, int> pii;
const int N = 5e5+7;
int n, m;
int a[20];
ll l, r;

struct Edge{
	int v, w;
};

vector<Edge> p[N];
priority_queue<pii, vector<pii>, greater<pii> > Q;
ll dis[N];
bool vis[N];

void dijk(int s){
	foreach(1, m, i) dis[i] = INF, vis[i] = 0;
	
	dis[s] = 0;
	Q.push({0, s});
	while(Q.size()){
		int u = Q.top().second;
		Q.pop();
		
		if(vis[u]) continue;
		vis[u] = 1;

		for(auto e: p[u]){
			int v = e.v, w = e.w;
			if(dis[u]+w < dis[v]){
				if(dis[u]+w<0) continue;
				dis[v] = dis[u] + w;
				Q.push({dis[v], v});
			}
		}
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> n >> l >> r;
	int minN = 5e5+7;
	foreach(1, n, i){
		int tmp;
		cin >> tmp;
		a[i] = tmp;
		if(tmp != 0) minN = min(minN, tmp);
	}

	m = minN;
	foreach(1, n, i){
		if(a[i] == 0 || a[i] == m) continue;//0对答案无贡献
		foreach(0, m-1, j){
			p[j].push_back({((j+a[i])%m), a[i]});
		}
	}

	dijk(0);
	ll ans1 = 0, ans2 = 0;
	foreach(0, m-1, i){
		ans1 += (dis[i] <= r) ? (r-dis[i])/m+1 : 0;
		ans2 += (dis[i] <= l-1) ? (l-1-dis[i])/m+1 : 0;
	}
	cout << ans1 - ans2;//类前缀和
}