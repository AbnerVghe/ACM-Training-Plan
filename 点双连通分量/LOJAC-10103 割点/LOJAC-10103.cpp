#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

typedef pair<int, int> pii;

const int N = 1e4+7;
int n, m;
int cntD, dfn[N], low[N];
vector<int> p[N];
int ans;
int block;

void init(){
	foreach(1, n, i) dfn[i] = low[i] = 0;
	cntD = block = 0;
	ans = 0;
}

void tarjan(int x, bool root){
	dfn[x] = low[x] = ++cntD;
	int son = 0, cut = 0;
	for(auto v: p[x]){
		if(!dfn[v]){
			tarjan(v, 0);
			son++;
			low[x] = min(low[x], low[v]);
			if(low[v] >= dfn[x]){
				if(!root){
					cut++;
				}
			}
		}
		else{
			low[x] = min(low[x], dfn[v]);
		}
	}

	if(root) ans = max(ans, son);
	else ans = max(ans, cut+1);
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	while(1){
		cin >> n >> m;
		if(!n && !m) break;
		foreach(1, m, i){
			int u, v;
			cin >> u >> v;
			u++, v++;
			p[u].push_back(v);
			p[v].push_back(u);
		}
		init();
		foreach(1, n, i){
			if(!dfn[i]){
				block++;
				tarjan(i, 1);
			}
		}  
		cout << block + ans - 1 << '\n';

		foreach(1, n, i) p[i].clear();
	}
}