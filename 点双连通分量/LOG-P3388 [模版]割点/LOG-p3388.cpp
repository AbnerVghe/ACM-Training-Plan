#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

typedef pair<int, int> pii;

const int N = 2e4+7;

int n, m;
vector<int> p[N];
int dfn[N], low[N], cntD;
bool cutVertex[N];

void tarjan(int x, bool root){
	dfn[x] = low[x] = ++cntD;
	int son = 0;
	for(auto v: p[x]){
		if(!dfn[v]){
			son++;
			tarjan(v, 0);
			low[x] = min(low[x], low[v]);
			if(low[v] >= dfn[x]){
				if(!root || son >= 2){
					cutVertex[x] = 1;
				}
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
	
	cin >> n >> m;
	foreach(1, m, i){
		int x, y;
		cin >> x >> y;
		p[x].push_back(y);
		p[y].push_back(x);
	}
	foreach(1, n, i){
		if(!dfn[i]) tarjan(i, 1);
	}
	int cnt = 0;
	foreach(1, n, i){
		if(cutVertex[i]) cnt++;
	}
	cout << cnt << '\n';
	foreach(1, n, i){
		if(cutVertex[i]) cout << i << ' ';
	}
}