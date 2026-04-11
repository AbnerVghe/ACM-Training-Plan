#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

typedef pair<int, int> pii;

const int N = 1e4+7;

int n, m;
int dfn[N], low[N];
int belong[N];
int cnt, cntd;
int stk[N];
int top;
int scc[N], sccl[N], sccr[N], idx;
bool vis[N];

vector<int> p[N];

void tarjan(int x){
	dfn[x] = low[x] = ++cntd;
	stk[++top] = x;
	for(auto v: p[x]){
		if(x == v) continue;

		if(!dfn[v]){
			tarjan(v);
			low[x] = min(low[x], low[v]);
		}
		else if(!belong[v]){
			low[x] = min(low[x], dfn[v]);
		}
	}

	if(dfn[x] == low[x]){
		cnt++;
		sccl[cnt] = idx + 1;
		int pop;
		do{
			pop = stk[top--];
			belong[pop] = cnt;
			scc[++idx] = pop;
		}while(pop != x);
		sccr[cnt] = idx;
	}
}


signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> n >> m;
	foreach(1, m, i){
		int u, v;
		cin >> u >> v;
		p[u].push_back(v);
	}
	foreach(1, n, i){
		if(!dfn[i]) tarjan(i);
	}
	cout << cnt << '\n';
	foreach(1, cnt, i){
		sort(scc+sccl[i], scc+sccr[i]+1);
	}
	foreach(1, n, i){
		int gp = belong[i];
		if(!vis[gp]){
			vis[gp] = 1;
			foreach(sccl[gp], sccr[gp], j){
				cout << scc[j] << ' ';
			}
			cout << '\n';
		}
	}
}