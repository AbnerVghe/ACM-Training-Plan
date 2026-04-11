#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

typedef pair<int, int> pii;

const int N = 3e5+7, M = 3e5+7;

int n, m;
int cntE = 1, head[N], to[2*M], nxt[2*M], weight[2*M];
int a[M], b[M], c[M];
int cntD;
int stk[N], top;
int dfn[N], low[N];
int ebccCnt, belong[N], val[N];
int s, t;

void init(){//清空链式前向星
	cntE = 0;
	foreach(1, ebccCnt, i){
		head[i] = 0;
	}
}

void add(int u, int v, int w){
	nxt[++cntE] = head[u];
	to[cntE] = v;
	weight[cntE] = w;
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

bool dfs(int x, int fa, bool ok){
	ok |= val[x];
	if(x == t){
		return ok;
	}

	for(int e = head[x]; e; e = nxt[e]){
		int v = to[e], w = weight[e];
		if(v == fa) continue;

		//return dfs(v, x, ok | w) is wrong!
		if(dfs(v, x, ok | w)) return 1;
	}
	return 0;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> n >> m;
	foreach(1, m, i){
		int u, v, z;
		cin >> u >> v >> z;
		a[i] = u, b[i] = v, c[i] = z;
		add(u, v, 0);
		add(v, u, 0);
	}
	tarjan(1, 0);
	init();
	foreach(1, m, i){
		int ebcc1 = belong[a[i]], ebcc2 = belong[b[i]];
		int w = c[i];
		if(ebcc1 == ebcc2){
			if(w) val[ebcc1] = 1;
		}
		else{
			add(ebcc1, ebcc2, w);
			add(ebcc2, ebcc1, w);
		}
	}
	cin >> s >> t;
	s = belong[s], t = belong[t];
	if(dfs(s, 0, 0)) cout << "YES";
	else cout << "NO";
}