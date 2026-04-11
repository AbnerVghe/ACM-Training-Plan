#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

typedef pair<int, int> pii;

const int N = 2e5+7;
int n;
int dfn[N], low[N], cntD;
vector<int> p[N];
int a, b;
int ans = N;

void tarjan(int x){
	dfn[x] = low[x] = ++cntD;

	for(auto v: p[x]){
		if(!dfn[v]){
			tarjan(v);
			low[x] = min(low[x], low[v]);
			if(low[v] >= dfn[x] && dfn[b] >= dfn[v] && b != x && a != x){
				ans = min(ans, x);
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
	
	cin >> n;
	while(1){
		int u, v;
		cin >> u >> v;
		if(!u && !v) break;
		p[u].push_back(v);
		p[v].push_back(u);
	}
	cin >> a >> b;
	tarjan(a);
	if(ans == N) cout << "No solution";
	else cout << ans;
}