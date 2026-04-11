#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

typedef pair<int, int> pii;

const int N = 3010;

vector<int> p[N];
int dfn[N], low[N], belong[N];
int stk[N], top;
int scc[N], sccMin[N], sccCnt;
int cntD;
int cost[N];
int rD[N];

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
		sccMin[sccCnt] = INF;
		do{
			pop = stk[top--];
			sccMin[sccCnt] = min(sccMin[sccCnt], cost[pop]);
			belong[pop] = sccCnt;
		}while(pop != x);
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n, m;
	cin >> n >> m;
	memset(cost, INF, sizeof cost);
	foreach(1, m, i){
		int x, c;
		cin >> x >> c;
		cost[x] = c;
	}
	int r;
	cin >> r;
	foreach(1, r, i){
		int a, b;
		cin >> a >> b;
		p[a].push_back(b);
	}

	foreach(1, n, i){
		if(!dfn[i] && cost[i] != INF) tarjan(i);
	}

	int ans = 0;
	foreach(1, n, i){
		if(!belong[i]){
			ans = i;
			break;
		}
	}
	if(ans){
		cout << "NO\n" << ans;
		return 0;
	}

	foreach(1, n, i){
		int scc1 = belong[i];
		for(auto v: p[i]){
			int scc2 = belong[v];
			if(scc1 != scc2){
				rD[scc2]++;
			}
		}
	}

	foreach(1, sccCnt, i){
		if(rD[i]) continue;
		ans += sccMin[i];
	}
	cout << "YES\n" << ans;
}