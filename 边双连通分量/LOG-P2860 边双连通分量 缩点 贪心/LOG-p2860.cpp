#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

typedef pair<int, int> pii;

const int N = 5010, M = 10010;

int n, m;
int cntE = 1, head[N], to[2*M], nxt[2*M];
int cntD;
int stk[N], top;
int dfn[N], low[N];
int ebccCnt, belong[N];
int degree[N];

void add(int u, int v){
	nxt[++cntE] = head[u];
	to[cntE] = v;
	head[u] = cntE;
}

void tarjan(int x, int preEdge){
	dfn[x] = low[x] = ++cntD;
	stk[++top] = x;
	
	for(int e = head[x]; e; e = nxt[e]){
		if((e^1) == preEdge) continue;

		int v = to[e];
		if(!dfn[v]){
			tarjan(v, e);
			low[x] = min(low[x], low[v]);
		}
		else{
			low[x] = min(low[x], dfn[v]);
		}
	}

	if(dfn[x] == low[x]){
		ebccCnt++;
		int pop;
		do{
			pop = stk[top--];
			belong[pop] = ebccCnt;
		}while(pop != x);
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> n >> m;
	foreach(1, m, i){
		int u, v;
		cin >> u >> v;
		add(u, v);
		add(v, u);
	}
	tarjan(1, 0);
	foreach(1, n, i){
		int ebcc1 = belong[i];
		for(int e = head[i]; e; e = nxt[e]){
			int v = to[e];
			int ebcc2 = belong[v];
			if(ebcc1 != ebcc2){
				degree[ebcc2]++;
			}
		}
	}
	int ans = 0, sum = 0;
	foreach(1, ebccCnt, i){
		if(degree[i] == 1) sum++;
	}
	ans = (sum+1)/2;
	cout << ans;
}