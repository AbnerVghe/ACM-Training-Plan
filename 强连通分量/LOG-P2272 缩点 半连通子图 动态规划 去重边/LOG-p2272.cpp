#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

typedef pair<int, int> pii;

const int N = 1e5+7, M = 1e6+7;

vector<int> p[N], p2[N];
int dfn[N], low[N], belong[N];
int stk[N], top;
int scc[N], sccCnt, sccSz[N];
int cntD;
int cntE;
ll edge[M];
int dpV[N], dpCnt[N];
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
		do{
			pop = stk[top--];
			belong[pop] = sccCnt;
			sccSz[sccCnt]++;
		}while(pop != x);
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n, m, mod;
	cin >> n >> m >> mod;
	foreach(1, m, i){
		int a, b;
		cin >> a >> b;
		p[a].push_back(b);
	}

	foreach(1, n, i){
		if(!dfn[i]) tarjan(i);
	}

	foreach(1, n, i){//缩点
		int scc1 = belong[i];
		for(auto v: p[i]){
			int scc2 = belong[v];
			if(scc1 != scc2){
				edge[++cntE] = ((ll)scc1<<32) | scc2;
			}
		}
	}
	sort(edge+1, edge+cntE+1);
	ll pre = 0, cur;
	foreach(1, cntE, i){
		cur = edge[i];
		if(cur != pre){
			int scc1 = (int)(cur>>32), scc2 = (int)(cur & 0xffffffffL);
			p2[scc1].push_back(scc2);
			rD[scc2]++;
			pre = cur;
		}

	}
	
	foreach(1, sccCnt, i){
		if(rD[i]) continue;
		dpV[i] = sccSz[i];
		dpCnt[i] = 1;
	}

	foreach_sub(sccCnt, 1, i){
		for(auto v: p2[i]){
			if(dpV[v] < dpV[i]+sccSz[v]){
				dpV[v] = dpV[i] + sccSz[v];
				dpCnt[v] = dpCnt[i];
			}
			else if(dpV[v] == dpV[i]+sccSz[v]){
				dpCnt[v] = (dpCnt[v] + dpCnt[i]) % mod;
			}
		}
	}

	int ans1 = 0, ans2 = 0;
	foreach(1, sccCnt, i){
		if(dpV[i] > ans1){
			ans1 = dpV[i];
			ans2 = dpCnt[i];
		}
		else if(dpV[i] == ans1){
			ans2 = (ans2 + dpCnt[i]) % mod;
		}
	}
	cout << ans1 << '\n' << ans2;
}