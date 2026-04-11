#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

typedef pair<int, int> pii;
const int N = 110;
int n, m;
int f[N][N];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> n >> m;
	memset(f, 0x3f3f3f3f, sizeof f);
	foreach(1, n, i) f[i][i] = 0;
	foreach(1, m, i){
		int u, v, w;
		cin >> u >> v >> w;
		f[u][v] = min(f[u][v], w), f[v][u] = min(f[v][u], w);
	}
	
	foreach(1, n, k) foreach(1, n, i) foreach(1, n, j){
		f[i][j] = min(f[i][j], f[i][k]+f[k][j]);
	}
	
	foreach(1, n, i)
	{
		foreach(1, n, j){
			cout << f[i][j] << ' '; 
		}
		cout << '\n';
	}
}