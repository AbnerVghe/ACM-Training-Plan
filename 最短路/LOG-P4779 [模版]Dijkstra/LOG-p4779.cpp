#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

typedef pair<int, int> pii;
const int N = 1e5+7;

struct Node{
	int v, w;
};

vector<Node> p[N];
int dis[N];
bool vis[N];
priority_queue<pii, vector<pii>, greater<pii> > Q; 
int n, m;

void dijkstra(int s){
	foreach(1, n, i){
		dis[i] = INF;
		vis[i] = 0;
	}
	while(Q.size()) Q.pop();

	dis[s] = 0;
	Q.push({0, s});
	while(Q.size()){
		int u = Q.top().second;
		Q.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		for(auto e: p[u]){
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
	
	int s;
	cin >> n >> m >> s;
	foreach(1, m, i){
		int u, v, w;
		cin >> u >> v >> w;
		p[u].push_back({v,w});
	}
	dijkstra(s);
	foreach(1, n, i){
		cout << dis[i] << ' ';
	}
}