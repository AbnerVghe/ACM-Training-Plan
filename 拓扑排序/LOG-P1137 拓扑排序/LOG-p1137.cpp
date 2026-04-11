#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

typedef pair<int, int> pii;

const int N = 1e5+7;
//int du[N], ans[N];

struct Node{
	int du, ans;
}node[N];

int n, m;

vector<int> p[N];
queue<int> Q;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> n >> m;
	foreach(1, n, i) node[i] = {0, 0};

	foreach(1, m, i){
		int x, y;
		cin >> x >> y;
		p[x].push_back(y);
		node[y].du++;
	}
	foreach(1, n, i){
		if(!node[i].du){
			Q.push(i);
			node[i].ans++;
		}
	}
	while(Q.size()){
		int u = Q.front();
		Q.pop();
		
		for(auto v: p[u]){
			node[v].ans = node[u].ans+1;
			node[v].du--;
			if(!node[v].du){
				Q.push(v);
			}
		}
	}
	
	foreach(1, n, i){
		cout << node[i].ans << '\n';
	}
}