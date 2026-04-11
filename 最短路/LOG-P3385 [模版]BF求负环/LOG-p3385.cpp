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

int dis[N];
vector<Edge> p[N];
int n, m;

bool bf(int s){
	foreach(1, n, i){
		dis[i] = INF;
	}

	dis[s] = 0;
	foreach(1, n, t){
		int cnt = 0;
		foreach(1, n, i){
			if(dis[i] == INF) continue;

			for(auto e: p[i]){
				int v = e.v, w = e.w;
				if(dis[i] + w < dis[v]){
					dis[v] = dis[i] + w;
					cnt++;
				}
			}
		}

		if(t == n && cnt == 0) return 0;//不存在负环
	}
	return 1;//存在负环
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
		
		if(bf(1)) cout << "YES";
		else cout << "NO";
		cout << '\n';
	
		foreach(1, n, i){
			p[i].clear();
		}
	}

	
}