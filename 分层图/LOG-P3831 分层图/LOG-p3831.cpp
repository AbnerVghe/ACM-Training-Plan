#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

typedef pair<int, int> pii;

const int N = 2e5+7;

struct Node{
	int x, y, id;
}node[N];

struct Edge{
	int v, w;
};

int n, m;
int s, t;
vector<Edge> p[N];
int dis[N];
bool vis[N];
priority_queue<pii, vector<pii>, greater<pii> > Q;

bool cmp1(Node &a, Node &b){
	if(a.y == b.y) return a.x < b.x;
	return a.y < b.y;
}

bool cmp2(Node &a, Node &b){
	if(a.x == b.x) return a.y < b.y;
	return a.x < b.x;
}

void build(){
	//建纵边图
	sort(node+1, node+m+1, cmp1);
	foreach(1, m-1, i){
		if(node[i].y == node[i+1].y){
			int p1 = node[i].id, p2 = node[i+1].id, w = 2*(node[i+1].x-node[i].x);
			p[p1].push_back({p2, w});
			p[p2].push_back({p1, w});
		}
	}

	//建横边图
	sort(node+1, node+m+1, cmp2);
	foreach(1, m-1, i){
		if(node[i].x == node[i+1].x){
			int p1 = node[i].id+m, p2 = node[i+1].id+m, w = 2*(node[i+1].y-node[i].y);
			p[p1].push_back({p2, w});
			p[p2].push_back({p1, w});
		}
	}

	//层与层之间的图
	foreach(1, m, i){
		int p1 = node[i].id, p2 = node[i].id+m;
		if(p1 == s || p1 == t){
			p[p1].push_back({p2, 0});
			p[p2].push_back({p1, 0});
		}
		else{
			p[p1].push_back({p2, 1});
			p[p2].push_back({p1, 1});
		}
	}
}

void dijk(){
	foreach(1, 2*m, i) dis[i] = INF, vis[i] = 0;

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
	m += 2;//顺便读入起点和终点
	foreach(1, m, i){
		int x, y;
		cin >> x >> y;
		node[i] = {x, y, i};
	}
	s = m-1, t = m;

	build();
	dijk();

	if(dis[t] == INF) cout << -1;
	else cout << dis[t];

}