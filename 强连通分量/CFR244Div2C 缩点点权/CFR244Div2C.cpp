#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

const int MOD  = 1e9+7;

typedef pair<int, int> pii;

const int N = 1e5+7;

vector<int> p[N];
int dfn[N], low[N], belong[N];
int stk[N], top;
int scc[N], sccMin[N], sccCnt, sccNum[N];
int cntD;
int cost[N];

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
			belong[pop] = sccCnt;

			if(cost[pop] < sccMin[sccCnt]){
				sccMin[sccCnt] = cost[pop];
				sccNum[sccCnt] = 0;
			}
			if(cost[pop] == sccMin[sccCnt]) sccNum[sccCnt]++;

		}while(pop != x);
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n;
	cin >> n;
	foreach(1, n, i){
		cin >> cost[i];
	}
	int m;
	cin >> m;
	foreach(1, m, i){
		int u, v;
		cin >> u >> v;
		p[u].push_back(v);
	}

	foreach(1, n, i){
		if(!dfn[i]) tarjan(i);
	}

	int ans1 = 0, ans2 = 1;
	foreach(1, sccCnt, i){
		ans1 += sccMin[i];
		ans2 = (ans2 * sccNum[i])%MOD;
	}
	cout << ans1 << ' ' << ans2;
}