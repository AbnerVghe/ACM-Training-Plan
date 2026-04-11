#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

struct Node{
	int d, x, cnt;
	bool operator < (const Node& a) const{
		return d > a.d;
	}
};

struct Edge{
	int v, w;
};

typedef pair<int, int> pii;

const int N = 1e4+7, K = 30;
int n, m, k;
int dis[N][K];
bool vis[N][K];
priority_queue<Node> Q;

vector<Edge> p[N];

void Dijk(int s){
	foreach(1, n, i) foreach(0, k, j){
		dis[i][j] = INF;
		vis[i][j] = 0;
	}

	dis[s][0] = 0;
	Q.push({0, s, 0});
	while(Q.size()){
		int x = Q.top().x, cnt = Q.top().cnt;
		Q.pop();
		
		
		if(vis[x][cnt]) continue;
		vis[x][cnt] = 1;

		for(auto e: p[x]){
			int v = e.v, w = e.w;
			if(dis[x][cnt]+w < dis[v][cnt]){
				dis[v][cnt] = dis[x][cnt] + w;
				Q.push({dis[v][cnt], v, cnt});
			}
			if(cnt < k && dis[x][cnt] < dis[v][cnt+1]){
				dis[v][cnt+1] = dis[x][cnt];
				Q.push({dis[v][cnt+1], v, cnt+1});
			}
		}
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> n >> m >> k;
	foreach(1, m, i){
		int u, v, w;
		cin >> u >> v >> w;
		p[u].push_back({v, w});
		p[v].push_back({u, w});
	}
	Dijk(1);
	int ans = INF;
	foreach(0, k, i){
		ans = min(ans, dis[n][i]);
	}
	cout << ans;
}