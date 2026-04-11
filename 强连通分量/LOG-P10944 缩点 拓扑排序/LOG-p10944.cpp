#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

typedef pair<int, int> pii;

const int N = 1010;

vector<int> p[N], p2[N];
int dfn[N], low[N], belong[N];
int stk[N], top;
int scc[N], sccCnt;
int cntD;
int rD[N];

void init(int n){
	foreach(1, n, i){
		dfn[i] = low[i] = belong[i] = rD[i] = 0;
	}
	sccCnt = top = cntD = 0;
}

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
		}while(pop != x);
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int T;
	cin >> T;
	while(T--){
		int n, m;
		cin >> n >> m;
		init(n);
		foreach(1, m, i){
			int u, v;
			cin >> u >> v;
			p[u].push_back(v);
		}
		foreach(1, n, i){
			if(!dfn[i]) tarjan(i);
		}
		foreach(1, n, i){
			int scc1 = belong[i];
			for(auto v: p[i]){
				int scc2 = belong[v];
				if(scc1 != scc2){
					p2[scc1].push_back(scc2);
					rD[scc2]++;
				}
			}
		}
		queue<int> Q;
		foreach(1, sccCnt, i){
			if(!rD[i]) Q.push(i);
		}
		bool ok = 1;
		while(Q.size()){
			if(Q.size()>1){
				ok = 0;
				break;
			}

			int u = Q.front();
			Q.pop();
			for(auto v: p2[u]){
				rD[v]--;
				if(!rD[v]){
					Q.push(v);
				}
			}
		}

		if(ok) cout << "Yes";
		else cout << "No";
		cout << '\n';

		foreach(1, n, i) p[i].clear();
		foreach(1, sccCnt, i) p2[i].clear();
	}
}