#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

typedef pair<int, int> pii;

const int N = 5e4+7;
int dfn[N], low[N], cntD;
int stk[N], top;
int vbccCnt;

vector<int> p[N], vbcc[N];

void tarjan(int x){
	low[x] = dfn[x] = ++cntD;
	stk[++top] = x;
	for(auto v: p[x]){
		if(!dfn[v]){
			tarjan(v);
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

bool cmp(vector<int> V1, vector<int> V2){
	int t = min(V1.size(), V2.size());
	foreach(0, t-1, i){
		if(V1[i] < V2[i]) return V1 < V2;
	}
	return V1.size() < V2.size();
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
		if(!dfn[i] && p[i].size()) tarjan(i);
	}
	foreach(1, vbccCnt, i){
		sort(vbcc[i].begin(), vbcc[i].end());
	}
	sort(vbcc+1, vbcc+vbccCnt+1, cmp);
	cout << vbccCnt << '\n';
	foreach(1, vbccCnt, i){
		for(auto x: vbcc[i]){
			cout << x << ' ';
		}
		cout << '\n';
	}

}