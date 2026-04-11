#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

typedef pair<int, int> pii;

const int N = 5e5 + 7;
int dfn[N], low[N], cntD;
int vbccCnt;
int stk[N], top;

vector<int> p[N], vbcc[N];

void tarjan(int x){//不需要判断根节点的割点性，否则会导致未成割点的根节点所在分量被忽略
	low[x] = dfn[x] = ++cntD;
	stk[++top] = x;
	int son = 0;
	for(auto v: p[x]){
		if(!dfn[v]){
			tarjan(v);
			son++;
			low[x] = min(low[x], low[v]);

			if(low[v] >= dfn[x]){
				vbccCnt++;
				int pop;
				do{
					pop = stk[top--];
					vbcc[vbccCnt].push_back(pop);
				}while(pop != v);
				vbcc[vbccCnt].push_back(x);
			}
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
	cin >> n >> m;
	foreach(1, m, i){
		int u, v;
		cin >> u >> v;
		if(u == v) continue;
		p[u].push_back(v);
		p[v].push_back(u);
	}
	foreach(1, n, i){
		if(!dfn[i]){
			if(p[i].size()) tarjan(i);
			else vbcc[++vbccCnt].push_back(i);
		}
	}
	cout << vbccCnt << '\n';
	foreach(1, vbccCnt, i){
		cout << vbcc[i].size() << ' ';
		for(auto v: vbcc[i]) cout << v << ' ';
		cout << '\n';
	}
}