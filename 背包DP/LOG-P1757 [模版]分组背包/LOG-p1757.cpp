#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 1010;

struct Node{
	int weight, val, gp;
}things[N];

int dp[N];

bool cmp(Node A, Node B){
	return A.gp < B.gp;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	int m, n;
	cin >> m >> n;
	foreach(1, n, i){
		int w, v, gp;
		cin >> w >> v >> gp;
		things[i] = {w, v, gp};
	}
	sort(things+1, things+n+1, cmp);
	int start = 1, end = 2;
	while(start <= n){
		while(end <= n && things[start].gp == things[end].gp) end++;
		foreach_sub(m, 0, j){
			foreach(start, end-1, i){
				if(j - things[i].weight >= 0){
					dp[j] = max(dp[j], dp[j-things[i].weight]+things[i].val);
				}
			}
		}
		start = end;
	}
	cout << dp[m];
}