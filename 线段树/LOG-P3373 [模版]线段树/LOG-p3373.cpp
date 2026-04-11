#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

typedef pair<int, int> pii;
const int N = 1e5+7;

int addTag[N << 2], mulTag[N << 2], sum[N << 2], a[N];

int m;

void push_up(int p){
	sum[p] = (sum[p << 1] + sum[p << 1 | 1]) % m;
}

void addLazy(int p, int v, int n){
	addTag[p] = (addTag[p] + v) % m;
	sum[p] = (sum[p] + (v*n) % m) % m;
}

void mulLazy(int p, int v){
	addTag[p] = (addTag[p] * v) % m;
	mulTag[p] = (mulTag[p] * v) % m;
	sum[p] = (sum[p] * v) % m;
}

void push_down(int p, int ln, int rn){
	if(mulTag[p] != 1){
		mulLazy(p << 1, mulTag[p]);
		mulLazy(p << 1 | 1, mulTag[p]);
		mulTag[p] = 1;
	}
	if(addTag[p]){
		addLazy(p << 1, addTag[p], ln);
		addLazy(p << 1 | 1, addTag[p], rn);
		addTag[p] = 0;
	}
}

void add(int L, int R, int v, int l, int r, int p){
	if(L <= l && r <= R){
		addLazy(p, v, r-l+1);
		return;
	}

	int mid = (l + r) >> 1;
	push_down(p, mid-l+1, r-mid);
	if(L <= mid){
		add(L, R, v, l, mid, p << 1);
	}
	if(R > mid){
		add(L, R, v, mid+1, r, p << 1 | 1);
	}
	push_up(p);
}

void mul(int L, int R, int v, int l, int r, int p){
	if(L <= l && r <= R){
		mulLazy(p, v);
		return;
	}

	int mid = (l + r) >> 1;
	push_down(p, mid-l+1, r-mid);
	if(L <= mid){
		mul(L, R, v, l, mid, p << 1);
	}
	if(R > mid){
		mul(L, R, v, mid+1, r, p << 1 | 1);
	}
	push_up(p);
}

int query(int L, int R, int l, int r, int p){
	if(L <= l && r <= R){
		return sum[p] % m;
	}
	
	int mid = (l + r) >> 1;
	push_down(p, mid-l+1, r-mid);
	int ans = 0;
	if(L <= mid){
		ans = (ans + query(L, R, l, mid, p << 1)) % m;
	}
	if(R > mid){
		ans = (ans + query(L, R, mid+1, r, p << 1 | 1)) % m;
	}
	return ans % m;
}

void build(int l, int r, int p){
	if(l == r){
		sum[p] = a[l];
		return;
	}

	int mid = (l + r) >> 1;
	build(l, mid, p << 1);
	build(mid+1, r, p << 1 | 1);
	push_up(p);
	addTag[p] = 0;
	mulTag[p] = 1;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	int n, q;
	cin >> n >> q >> m;
	foreach(1, n, i){
		cin >> a[i];
	}
	build(1, n, 1);
	foreach(1, q, i){
		int opt, x, y;
		cin >> opt >> x >> y;
		if(opt == 3){
			cout << (query(x, y, 1, n, 1))%m << '\n';
		}
		else{
			int k;
			cin >> k;
			if(opt == 1){
				mul(x, y, k, 1, n, 1);
			}
			else{
				add(x, y, k, 1, n, 1);
			}
		}
	}
}