#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

typedef pair<int, int> pii;

struct Node{
	int x, d;
};

const int N= 1e5+7;
deque<Node> Q;
int k;
ll ans;
bool vis[N];

void add(int v, int d, int w){
	if(w) Q.push_back({v, d+w});
	else Q.push_front({v, d});
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> k;
	Q.push_back({1, 1});
	vis[1] = 1;
	while(Q.size()){
		int u = Q.front().x, d = Q.front().d;
		Q.pop_front();

		if(u == 0){
			ans = d;
			break;
		}

		int v;
		v = (u*10) % k;
		if(!vis[v]){
			add(v, d, 0);
			vis[v] = 1;
		}
		v = (u+1) % k;
		if(!vis[v]){
			add(v, d, 1);
		}
	}

	cout << ans;
}