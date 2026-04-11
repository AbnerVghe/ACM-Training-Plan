#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

typedef pair<int, int> pii;

const int N = 5e3+7;

vector<int> p[N];

int dfn[N], low[N], belong[N];
int sccCnt, sccL[N], sccR[N], sccSz[N];
int scc[N];
int stk[N], top, idx;
int dCnt;

void tarjan(int x){
	dfn[x] = low[x] = ++dCnt;
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

	if(dfn[x] == low[x]){
		sccCnt++;
		int pop;
		sccL[sccCnt] = idx+1;
		do{
			pop = stk[top--];
			sccSz[sccCnt]++;
			belong[pop] = sccCnt;
			scc[++idx] = pop;
		}while(pop != x);
		sccR[sccCnt] = idx;
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	int n, m;
	cin >> n >> m;
	foreach(1, m, i){
		int a, b, t;
		cin >> a >> b >> t;
		p[a].push_back(b);
		if(t == 2) p[b].push_back(a);
	}
	foreach(1, n, i){
		if(!dfn[i]) tarjan(i);
	}
	int maxSz = -1;
	foreach(1, sccCnt, i){
		sort(scc+sccL[i], scc+sccR[i]+1);
		maxSz = max(maxSz, sccSz[i]);
	}
	cout << maxSz << '\n';
	foreach(1, n, i){
		int bl = belong[i];
		if(maxSz == sccSz[bl]){
			foreach(sccL[bl], sccR[bl], j){
				cout << scc[j] << ' ';
			}
			break;
		}
	}

}