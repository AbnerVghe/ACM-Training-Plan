#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

typedef pair<int, int> pii;

//向上取整：x/k -> (x+k-1)/k

const int N = 1e4+7, K = 110;

struct Edge{
	int v, a;
};

priority_queue<pii, vector<pii>, greater<pii> > Q;
int n, m, k;
int dis[N][K];
bool vis[N][K];
vector<Edge> p[N];

void Dijk(){
	foreach(1, n, i) foreach(0, k, j) dis[i][j] = INF, vis[i][j] = 0;

	dis[1][0] = 0;
	Q.push({0, 1});
	while(Q.size()){
		int u = Q.top().second, t = Q.top().first;
		Q.pop();

		if(vis[u][t%k]) continue;
		vis[u][t%k] = 1;

		for(auto e: p[u]){
			int v = e.v, a = e.a;
			
			int tmp = t;
			if(tmp < a) tmp += ((a-tmp+k-1) / k) * k;

			if(tmp + 1 < dis[v][(tmp+1)%k]){
				dis[v][(tmp+1)%k] = tmp + 1;
				Q.push({tmp+1, v});
			}
		}
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> n >> m >> k;
	foreach(1, m, i){
		int u, v, a;
		cin >> u >> v >> a;
		p[u].push_back({v, a});
	}

	Dijk();
	if(dis[n][0] == INF) cout << -1;
	else cout << dis[n][0];


}