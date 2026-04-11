#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

typedef pair<int, int> pii;

const int N = 510;
int dfn[N], low[N], cntD;
int vbccCnt, cutVertex[N], stk[N], top;
int n;
vector<int> p[N], vbcc[N];

void init(){
	cntD = vbccCnt = top = 0;
	foreach(1, n, i){
		dfn[i] = low[i] = cutVertex[i] = 0;
	}
}

void tarjan(int x, bool root){
	dfn[x] = low[x] = ++cntD;
	stk[++top] = x;
	int son = 0;
	for(auto v: p[x]){
		if(!dfn[v]){
			tarjan(v, 0);
			son++;
			low[x] = min(low[x], low[v]);
			if(low[v] >= dfn[x]){
				if(!root || son >= 2){
					cutVertex[x] = 1;
				}

				vbccCnt++;
				int pop;
				vbcc[vbccCnt].push_back(x);
				do{
					pop = stk[top--];
					//vbccSz[vbccCnt]++;
					vbcc[vbccCnt].push_back(pop);
				}while(pop != v);
			}
		}
		else{
			low[x] = min(low[x], dfn[v]);
		}
	}
}

void printAns(int t, int ans1, int ans2){
	cout << "Case " << t << ": " << ans1 << ' ' << ans2 << '\n';
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	int T = 0;
	while(++T){
		int m;
		cin >> m;
		if(!m) break;
		int mx = 0;
		foreach(1, m, i){
			int u, v;
			cin >> u >> v;
			p[u].push_back(v);
			p[v].push_back(u);
			mx = max(mx, max(u, v));
		}
		n = mx;
		init();
		tarjan(n, 1);
		if(vbccCnt == 1){
			int tn = vbcc[1].size();
			printAns(T, 2, tn*(tn-1)/2);
		}
		else{
			int ans1 = 0, ans2 = 1;
			foreach(1, vbccCnt, i){
				int cnt = 0;
				for(auto x: vbcc[i]){
					if(cutVertex[x]) cnt++;
				}
				if(cnt >= 2) continue;
				ans1++;
				ans2 *= vbcc[i].size() - 1;
			}
			printAns(T, ans1, ans2);
		}

		foreach(1, n, i) p[i].clear();
		foreach(1, vbccCnt, i) vbcc[i].clear();
	}
}