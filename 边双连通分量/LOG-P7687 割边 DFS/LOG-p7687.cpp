#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

typedef pair<int, int> pii;

const int N = 1e5, M = 1e6;
int acnt[N], bcnt[N] , head[N], to[2*M], nxt[2*M];
int cntE = 1;
int dfn[N], low[N], cntD;
int k, l;
int cntA;
int ansU[M], ansV[M];

void add(int u, int v){
	nxt[++cntE] = head[u];
	to[cntE] = v;
	head[u] = cntE;
}

void tarjan(int x, int preEdge){
	dfn[x] = low[x] = ++cntD;

	for(int e = head[x]; e; e = nxt[e]){
		if((e^1) == preEdge) continue;

		int v = to[e];
		if(!dfn[v]){
			tarjan(v, e);
			low[x] = min(low[x], low[v]);
			if(low[v] > dfn[x]){
				if(acnt[v]==0 || acnt[v]==k || bcnt[v]==0 || bcnt[v]==l){
					cntA++;
					ansU[cntA] = x;
					ansV[cntA] = v;
				}
			}

			acnt[x] += acnt[v];
			bcnt[x] += bcnt[v];
		}
		else{
			low[x] = min(low[x], dfn[v]);
		}
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	int n, m;
	cin >> n >> m >> k >> l;
	foreach(1, k, i){
		int tmp;
		cin >> tmp;
		acnt[tmp]++;
	}
	foreach(1, l, i){
		int tmp;
		cin >> tmp;
		bcnt[tmp]++;
	}
	foreach(1, m, i){
		int p, q;
		cin >> p >> q;
		add(p, q);
		add(q, p);
	}
	tarjan(1, 0);
	cout << cntA << '\n';
	foreach(1, cntA, i){
		cout << ansU[i] << ' ' << ansV[i] << '\n';
	}
	
}