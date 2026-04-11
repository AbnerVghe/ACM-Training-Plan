#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

typedef pair<int, int> pii;

const int N = 60;
struct Node{
	int d, x, cnt;
	bool operator < (const Node& a) const{
		return d > a.d;
	}
};
struct Edge{
	int v, w;
};
int n, m, k;
int dis[N][N];
bool vis[N][N];
vector<Edge> p[N];

priority_queue<Node> Q;

void Dijk(int s){
	foreach(1, n, i) foreach(0, k, j) dis[i][j] = INF, vis[i][j] = 0;

	dis[s][0] = 0;
	Q.push({0, s, 0});
	while(Q.size()){
		int u = Q.top().x, cnt = Q.top().cnt;
		Q.pop();
		
		if(vis[u][cnt]) continue;
		vis[u][cnt] = 1;

		for(auto e: p[u]){
			int v = e.v, w = e.w;
			if(dis[u][cnt] + w < dis[v][cnt]){
				dis[v][cnt] = dis[u][cnt] + w;
				Q.push({dis[v][cnt], v, cnt});
			}
			if(cnt < k && dis[u][cnt] + w/2 < dis[v][cnt+1]){
				dis[v][cnt+1] = dis[u][cnt] + w/2;
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
		int a, b, t;
		cin >> a >> b >> t;
		p[a].push_back({b, t});
		p[b].push_back({a, t});
	}
	Dijk(1);
	int ans = INF;
	foreach(0, k, i){
		ans = min(ans, dis[n][i]);
	}
	cout << ans;
	
}