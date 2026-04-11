#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

typedef pair<int, int> pii;

struct Node{
	int v, w;
};

const int N = 1010;
int n, m;
vector<Node> p[N];
int dis[N], cnt[N], st[N];
queue<int> q;

bool SPFA(int s){
	foreach(1, n, i) dis[i] = INF, cnt[i] = 0, st[i] = 0;
	while(q.size()) q.pop();

	dis[s] = 0;
	q.push(s);
	st[s] = 1;
	while(q.size()){
		int u = q.front();
		q.pop();
		st[u] = 0;

		for(auto e: p[u]){
			int v = e.v, w = e.w;
			if(dis[u] + w < dis[v]){
				dis[v] = dis[u] + w;
				cnt[v] = cnt[u] + 1;

				if(cnt[v] >= n) return 1;

				if(!st[v]){
					q.push(v);
					st[v] = 1;
				}
			}
		}
	}
	return 0;

}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> n >> m;
	foreach(1, m, i){
		int u, v, w;
		cin >> u >> v >> w;
		p[u].push_back({v, -w});
	}
	ll ans1 = -INF, ans2 = -INF;
	if(!SPFA(1)) ans1 = dis[n];
	if(!SPFA(n)) ans2 = dis[1];
	
	ll ans = min(ans1, ans2);
	if(ans == -INF) cout << "Forever love";
	else cout << ans;
	

}