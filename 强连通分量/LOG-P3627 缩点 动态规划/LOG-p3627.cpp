#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

typedef pair<int, int> pii;

const int N = 5e5+7;

vector<int> p[N], p2[N];
int dfn[N], low[N], belong[N];
int stk[N], top;
int scc[N], sccCnt, sccW[N];
bool sccJB[N];
int cntD;
int dp[N];
int cost[N];
bool JB[N];

void tarjan(int x){
	low[x] = dfn[x] = ++cntD;
	stk[++top] = x;

	for(auto v: p[x]){
		if(!dfn[v]){
			tarjan(v);
			low[x] = min(low[x], low[v]);
		}
		else if(!belong[v]){
			low[x] = min(low[x], dfn[v]);
		}
	}

	if(low[x] == dfn[x]){
		sccCnt++;
		int pop;
		do{
			pop = stk[top--];
			belong[pop] = sccCnt;
			sccW[sccCnt] += cost[pop];
			if(JB[pop]) sccJB[sccCnt] = 1;
		}while(pop != x);
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
		p[u].push_back(v);
	}
	foreach(1, n, i){
		int c;
		cin >> c;
		cost[i] = c;
	}
	int s;
	cin >> s;
	int P;
	cin >> P;
	foreach(1, P, i){
		int x;
		cin >> x;
		JB[x] = 1;
	}
	tarjan(s);

	foreach(1, n, i){
		int scc1 = belong[i];
		if(!scc1) continue;
		for(auto v: p[i]){
			int scc2 = belong[v];
			if(!scc2) continue;

			p2[scc1].push_back(scc2);
		}
	}

	foreach_sub(sccCnt, 1, i){
		dp[i] += sccW[i];
		for(auto v: p2[i]){
			dp[v] = max(dp[v], dp[i]);
		}
	}

	int ans = 0;
	foreach(1, sccCnt, i){
		if(sccJB[i]){
			ans = max(ans, dp[i]);
		}
	}
	cout << ans;
}