#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

typedef pair<int, int> pii;

const int N = 2e3 + 7;
struct Edge{
	int v, w;
};

int dis[N], cnt[N];
vector<Edge> p[N];
int n, m;
bool vis[N];
queue<int> Q;

bool spfa(int s){
	foreach(1, n, i) dis[i] = INF, vis[i] = 0, cnt[i] = 0;
	while(Q.size()) Q.pop();

	dis[s] = 0;
	vis[s] = 1;
	Q.push(s);
	while(Q.size()){
		int u = Q.front();
		Q.pop();
		vis[u] = 0;

		for(auto e: p[u]){
			int v = e.v, w = e.w;
			if(dis[u]+w < dis[v]){
				dis[v] = dis[u] + w;
				cnt[v] = cnt[u] + 1;
				
				if(cnt[v] >= n) return 1;

				if(!vis[v]){
					Q.push(v);
					vis[v] = 1;
				}
			}
			
		}
	}
	return 0;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	int T;
	cin >> T;
	while(T--){
		cin >> n >> m;
		foreach(1, m, i){
			int u, v, w;
			cin >> u >> v >> w;
			p[u].push_back({v,w});
			if(w>=0) p[v].push_back({u,w});
		}
		
		if(spfa(1)) cout << "YES";
		else cout << "NO";
		cout << '\n';
	
		foreach(1, n, i){
			p[i].clear();
		}
	}

	
}