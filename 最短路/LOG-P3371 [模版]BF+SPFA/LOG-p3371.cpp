#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

typedef pair<int, int> pii;

const int N = 1e4+7;
struct Edge{
	int v, w;
};

int n, m, s;
vector<Edge> p[N];
int dis[N];
queue<int> Q;
bool in[N];

void BF(int s){
	foreach(1, n, i){
		dis[i] = INF;
	}

	dis[s] = 0;
	Q.push(s);
	in[s] = 1;

	while(Q.size()){
		int i = Q.front();
		Q.pop();
		in[i] = 0;

		for(auto e: p[i]){
			int v = e.v, w = e.w;
			if(dis[i]+w < dis[v]){
				dis[v] = dis[i] + w;
				if(!in[v]){
					Q.push(v);
					in[v] = 1;
				}
			}
		}

	}

}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> n >> m >> s;
	foreach(1, m, i){
		int u, v, w;
		cin >> u >> v >> w;
		p[u].push_back({v,w});
	}
	BF(s);
	foreach(1, n, i){
		cout << ((dis[i] == INF) ? ((1<<31)-1) : dis[i]) << ' ';
	}

}