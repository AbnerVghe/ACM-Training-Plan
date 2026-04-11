#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

typedef pair<int, int> pii;

const int N = 5e5+7, M = 2e6+7;

int head[N], to[2*M], nxt[2*M];
int cntE = 1, cntD;
int dfn[N], low[N];
bool vis[M];

void add(int u, int v){
	nxt[++cntE] = head[u];
	to[cntE] = v;
	head[u] = cntE;
}

void tarjan(int x, int preEdge){
	dfn[x] = low[x] = ++cntD;
	for(int e = head[x]; e; e = nxt[e]){
		if((e^1) == preEdge) continue;
	
		int v = to[e];
		if(!dfn[v]){
			tarjan(v, e);
			low[x] = min(low[x], low[v]);
			if(low[v] > dfn[x]){
				vis[e >> 1] = 1;
			}
		}
		else{
			low[x] = min(low[x], dfn[v]);
		}
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	int n, m;
	cin >> n >> m;
	foreach(1, m, i){
		int u, v;
		cin >> u >> v;
		add(u, v);
		add(v, u);
	}
	foreach(1, n, i){
		if(!dfn[i]) tarjan(i, 0);
	}
	int c = 0;
	foreach(1, m, i){
		if(vis[i]) c++;
	}
	cout << c << '\n';
	foreach(1, m, i){
		if(vis[i]) cout << i << ' ';
	}
}