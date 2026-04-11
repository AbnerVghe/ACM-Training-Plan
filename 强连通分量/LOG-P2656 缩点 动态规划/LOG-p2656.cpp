#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

typedef pair<int, int> pii;

const int N = 8e4+7;

struct Edge{
	int v, w, rate;
};

vector<Edge> p[N], p2[N];
int dfn[N], low[N], belong[N];
int stk[N], top;
int scc[N], sccCnt, sccW[N];
int cntD;
int dp[N];
int rD[N];

void tarjan(int x){
	low[x] = dfn[x] = ++cntD;
	stk[++top] = x;

	for(auto e: p[x]){
		int v = e.v;
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
		}while(pop != x);
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n, m;
	cin >> n >> m;
	foreach(1, m, i){
		int u, v, w;
		double r;
		cin >> u >> v >> w >> r;
		r *= 10;
		p[u].push_back({v, w, int(r)});
	}
	int s;
	cin >> s;
	tarjan(s);
	foreach(1, n, i){
		int scc1 = belong[i];
		if(!scc1) continue;
		for(auto e: p[i]){
			int v = e.v;
			int scc2 = belong[v];
			if(!scc2) continue;
			if(scc1 == scc2){
				int w = e.w, r = e.rate;
				do{
					sccW[scc1] += w;
					w = w * r / 10;
				}while(w);
			}
			else{
				p2[scc1].push_back({scc2, e.w});
				//rD[scc2]++;
			}
		}
	}
	foreach_sub(sccCnt, 1, i){
		dp[i] += sccW[i];
		for(auto e: p2[i]){
			int v = e.v, w = e.w;
			dp[v] = max(dp[v], dp[i]+w);
		}
	}
	/*queue<int> Q;
	Q.push(s);
	while(Q.size()){
		int u = Q.front();
		Q.pop();
		dp[u] += sccW[u];
		for(auto e: p2[u]){
			int v = e.v, w = e.w;
			dp[v] = max(dp[v], dp[u]+w);
			rD[v]--;
			if(!rD[v]){
				Q.push(v);
			}
		}
	}*/

	int ans = 0;
	foreach(1, sccCnt, i){
		ans = max(ans, dp[i]);
	}
	cout << ans;
}