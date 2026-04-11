#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

typedef pair<int, int> pii;
const int N = 1010;
priority_queue<pii, vector<pii>, greater<pii> > Q;
int n, m;
int dis[N];
bool vis[N];

struct Node{
	int v, w;
};

vector<Node> p[N][2];

void Dijk(int s, int opt){
	while(Q.size()) Q.pop();
	foreach(1, n, i) dis[i] = INF, vis[i] = 0;
	
	dis[s] = 0;
	Q.push({0, s});
	while(Q.size()){
		int u = Q.top().second;
		Q.pop();
		
		if(vis[u]) continue;
		vis[u] = 1;

		for(auto e: p[u][opt]){
			int v = e.v, w = e.w;
			if(dis[u] + w < dis[v]){
				dis[v] = dis[u] + w;
				Q.push({dis[v], v});
			}
		}
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> n >> m;
	foreach(1, m, i){
		int u, v, w;
		cin >> u >> v >> w;
		p[u][0].push_back({v, w});
		p[v][1].push_back({u, w});
	}
	ll ans = 0;
	Dijk(1, 0);
	foreach(1, n, i){
		ans += dis[i];
	}
	Dijk(1, 1);
	foreach(1, n, i){
		ans += dis[i];
	}
	cout << ans;
}