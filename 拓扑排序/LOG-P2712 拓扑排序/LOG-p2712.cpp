#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

typedef pair<int, int> pii;
const int N = 110, M = 10010;
int viscnt;
int n;
int cnt = 1, head[N], nxt[M], to[M], du[N];

vector<int> p[N], dot[N*5];

void add(int u, int v){
	nxt[cnt] = head[u];
	to[cnt] = v;
	du[v]++;
	head[u] = cnt++;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> n;
	foreach(1, n, i){
		int x, m;
		cin >> x >> m;
		dot[x].push_back(i);
		foreach(1, m, j){
			int tmp;
			cin >> tmp;
			p[i].push_back(tmp);
		}
	}
	foreach(1, n, i){
		for(auto e: p[i]){
			for(auto ei: dot[e]){
				add(i, ei);
			}
		}
	}
	queue<int> Q;
	foreach(1, n, i){
		if(!du[i]) Q.push(i);
	}
	while(Q.size()){
		int u = Q.front();
		viscnt++;
		Q.pop();
		for(int i = head[u]; i; i = nxt[i]){
			du[to[i]]--;
			if(!du[to[i]]) Q.push(to[i]);
		}
	}
	if(viscnt == n) cout << "YES";
	else cout << n - viscnt;
}