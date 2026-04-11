#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

typedef pair<int, int> pii;

const int N = 8010;

unordered_map<string, int> mp;
vector<int> p[N];
int dfn[N], low[N], belong[N];
int stk[N], top;
int scc[N], sccCnt;
int cntD;
int rD[N];
int cntP;
int marry[N][2];

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

	int n;
	cin >> n;
	foreach(1, n, i){
		string a, b;
		cin >> a >> b;
		if(!mp.count(a)) mp[a] = ++cntP;
		if(!mp.count(b)) mp[b] = ++cntP;
		int na = mp[a], nb = mp[b];

		marry[i][0] = na, marry[i][1] = nb;
		p[na].push_back(nb);
	}
	int m;
	cin >> m;
	foreach(1, m, i){
		string a, b;
		cin >> a >> b;
		int na = mp[a], nb = mp[b];

		p[nb].push_back(na);
	}

	foreach(1, cntP, i){
		if(!dfn[i]) tarjan(i);
	}

	foreach(1, n, i){
		int p1 = marry[i][0], p2 = marry[i][1];
		int scc1 = belong[p1], scc2 = belong[p2];
		if(scc1 == scc2){
			cout << "Unsafe";
		}
		else cout << "Safe";

		cout << '\n';
	}
}