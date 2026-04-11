#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

typedef pair<int, int> pii;

const int N = 5e5+7, M = 2e6+7;
int acnt[N], bcnt[N] , head[N], to[2*M], nxt[2*M];
int cntE = 1;
int dfn[N], low[N], cntD;
int stk[N], top;
int bccCnt, bccSz[N], bcc[N], bccL[N], bccR[N], idx;

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

	if(low[x] == dfn[x]){
			bccCnt++;
			int pop;
			bccL[bccCnt] = idx + 1;
			do{
				pop = stk[top--];
				bccSz[bccCnt]++;
				bcc[++idx] = pop;
			}while(pop != x);
			bccR[bccCnt] = idx;
		}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	int n, m;
	cin >> n >> m;
	foreach(1, m, i){
		int p, q;
		cin >> p >> q;
		add(p, q);
		add(q, p);
	}
	foreach(1, n, i){
		if(!dfn[i]) tarjan(i, 0);
	}
	cout << bccCnt << '\n';
	foreach(1, bccCnt, i){
		cout << bccSz[i] << ' ';
		foreach(bccL[i], bccR[i], j){
			cout << bcc[j] << ' ';
		}
		cout << '\n';
	}
	
}