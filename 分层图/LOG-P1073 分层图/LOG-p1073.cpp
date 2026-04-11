#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f
typedef pair<int, int> pii;

const int N = 1e5+7;

struct Node{
	int x, cnt;
};

int n, m;
int a[N];
int dis[N][3];
bool vis[N][3];
queue<Node> Q;
vector<int> p[N];

void SPFA(){//SPFA最长路
	foreach(1, n, i) foreach(0, 2, j) dis[i][j] = -INF, vis[i][j] = 0;

	dis[1][0] = 0;
	Q.push({1, 0});
	vis[1][0] = 1;
	while(Q.size()){
		int u = Q.front().x, cnt = Q.front().cnt;
		Q.pop();
		vis[u][cnt] = 0;

		for(auto v: p[u]){
			if(dis[u][cnt] > dis[v][cnt]){
				dis[v][cnt] = dis[u][cnt];
				if(!vis[v][cnt]){
					Q.push({v, cnt});
					vis[v][cnt] = 1;
				}
			}
		}

		if(cnt == 0){
			if(dis[u][cnt]-a[u] > dis[u][cnt+1]){
				dis[u][cnt+1] = dis[u][cnt] - a[u];
				if(!vis[u][cnt+1]){
					Q.push({u, cnt+1});
					vis[u][cnt+1] = 1;
				}
			}
		}
		else if(cnt == 1){
			if(dis[u][cnt]+a[u] > dis[u][cnt+1]){
				dis[u][cnt+1] = dis[u][cnt] + a[u];
				if(!vis[u][cnt+1]){
					Q.push({u, cnt+1});
					vis[u][cnt+1] = 1;
				}
			}
		}
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> n >> m;
	foreach(1, n, i){
		cin >> a[i];
	}
	foreach(1, m, i){
		int x, y, z;
		cin >> x >> y >> z;
		p[x].push_back(y);
		if(z == 2) p[y].push_back(x);
	}
	SPFA();
	cout << dis[n][2];
}