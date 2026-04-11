#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

typedef pair<int, int> pii;

const int N = 1e5+7, M = 3e5+7;

int cntE = 1, head[N], to[2*M], nxt[2*M];
int dfn[N], low[N];
int cntD;
int cntA;
int ansU[M], ansV[M];
bool cutEdge;

int n, m;

void add(int u, int v){
	nxt[++cntE] = head[u];
	to[cntE] = v;
	head[u] = cntE;
}

void addAns(int u, int v){
	cntA++;
	ansU[cntA] = u, ansV[cntA] = v;
}

void tarjan(int x, int preEdge){
	dfn[x] = low[x] = ++cntD;

	for(int e = head[x]; e; e = nxt[e]){
		if((e^1) == preEdge) continue;

		int v = to[e];
		if(!dfn[v]){
			addAns(x, v);
			tarjan(v, e);
			low[x] = min(low[x], low[v]);
			
			if(low[v] > dfn[x]){
				cutEdge = 1;
				return;
			}
		}
		else if(dfn[v] < dfn[x]){
			addAns(x, v);
			low[x] = min(low[x], dfn[v]);
		}
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> n >> m;
	foreach(1, m ,i){
		int a, b;
		cin >> a >> b;
		add(a, b);
		add(b, a);
	}
	tarjan(1, 0);
	if(cutEdge) cout << 0;
	else{
		foreach(1, cntA, i){
			cout << ansU[i] << ' ' << ansV[i] << '\n';	
		}
	}
}