#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

typedef pair<int, int> pii;
const int M = 6010, N = 210;

struct Edge{
	int u, v, w;
}edge[M];

bool cmp(Edge A, Edge B){
	return A.w < B.w;
}

int n, W;
int fa[N];

void init(){
	foreach(1, n, i){
		fa[i] = i;
	}
}

int find(int i){
	if(fa[i] != i){
		fa[i] = find(fa[i]);
	}
	return fa[i];
}

bool add(int x, int y){
	int fx = find(x), fy = find(y);
	if(fx != fy){
		fa[fx] = fy;
		return 1;
	}
	return 0;
}

int kruskal(int nw){
	if(nw < n-1) return -1;

	init();
	int cnt = 0, ans = 0;
	foreach(1, nw, i){
		int u = edge[i].u, v = edge[i].v, w = edge[i].w;
		if(add(u, v)){
			cnt++;
			ans += w;
		}

		if(cnt == n-1) break;
	}
	if(cnt == n-1) return ans;
	else return -1;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> n >> W;
	foreach(1, W, i){
		int u, v, w;
		cin >> u >> v >> w;
		edge[i] = {u, v, w};
		stable_sort(edge+1, edge+i+1, cmp);
		cout << kruskal(i) << '\n';
	}
	
}