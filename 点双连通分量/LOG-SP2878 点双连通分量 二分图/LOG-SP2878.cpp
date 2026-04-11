#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

typedef pair<int, int> pii;

const int N = 1010;
int hate[N][N];
int dfn[N], low[N], cntD;
int vbccCnt, stk[N], top;
int n, m;
vector<int> p[N], vbcc[N];
bool curVertex[N], color[N];
bool ok[N];

void init(){
	foreach(1, n, i) foreach(1, n, j) hate[i][j] = 0;
	cntD = vbccCnt = top = 0;
	foreach(1, n, i){
		dfn[i] = low[i] = curVertex[i] = color[i] = ok[i] = 0;
	}
}

void tarjan(int x){
	dfn[x] = low[x] = ++cntD;
	stk[++top] = x;
	for(auto v: p[x]){
		if(!dfn[v]){
			tarjan(v);
			low[x] = min(low[x], low[v]);
			if(low[v] >= dfn[x]){
				vbccCnt++;
				int pop;
				vbcc[vbccCnt].push_back(x);
				do{
					pop = stk[top--];
					vbcc[vbccCnt].push_back(pop);
				}while(pop != v);
			}
		}
		else{
			low[x] = min(low[x], dfn[v]);
		}
	}
}

bool oddCheck(int x, int c){
	color[x] = c;
	for(auto v: p[x]){
		if(curVertex[v]){
			if(color[v] == c) return 1;
			if(!color[v] && oddCheck(v, c==1 ? 2 : 1)) return 1;
		}
	}
	return 0;
}

int compute(){
	foreach(1, vbccCnt, i){
		for(auto x: vbcc[i]){
			color[x] = 0;
			curVertex[x] = 1;
		}
		bool check = oddCheck(vbcc[i][0], 1);
		for(auto x: vbcc[i]){
			ok[x] |= check;
			curVertex[x] = 0;
		}
	}
	int ans = 0;
	foreach(1, n, i) if(!ok[i]) ans++;

	return ans;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	while(1){
		cin >> n >> m;
		if(!n && !m) break;

		init();
		foreach(1, m, i){
			int u, v;
			cin >> u >> v;
			hate[u][v] = 1;
			hate[v][u] = 1;
		}
		foreach(1, n, i){
			foreach(1, n, j){
				if(i == j || hate[i][j]) continue;
				p[i].push_back(j);
			}
		}
		foreach(1, n, i){
			if(!dfn[i]) tarjan(i);
		}

		int ans = compute();
		//cout << vbccCnt << ' ';
		cout << ans << '\n';

		foreach(1, n, i) p[i].clear();
		foreach(1, vbccCnt, i) vbcc[i].clear();
	}
}