#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

typedef pair<int, int> pii;

const int N = 1e6+7;
int addTag[N << 2], changeTag[N << 2], tr[N << 2] , a[N];
bool updateTag[N << 2];

void push_up(int p){
	tr[p] = max(tr[p << 1], tr[p << 1 | 1]);
}

void addLazy(int p, int v){
	tr[p] += v;
	addTag[p] += v;
}

void changeLazy(int p, int v){
	tr[p] = v;
	changeTag[p] = v;
	updateTag[p] = 1;
	addTag[p] = 0;
}

void push_down(int p){
	if(updateTag[p]){
		changeLazy(p << 1, changeTag[p]);
		changeLazy(p << 1 | 1, changeTag[p]);
		updateTag[p] = 0;
	}
	if(addTag[p]){
		addLazy(p << 1, addTag[p]);
		addLazy(p << 1 | 1, addTag[p]);
		addTag[p] = 0;
	}
}

void build(int l, int r, int p){
	if(l == r){
		tr[p] = a[l];
		return;
	}

	int mid = (l + r) >> 1;
	build(l, mid, p << 1);
	build(mid+1, r, p << 1 | 1);
	push_up(p);
	changeTag[p] = addTag[p] = updateTag[p] = 0;
}

void add(int L, int R, int v, int l, int r, int p){
	if(L <= l && r <= R){
		addLazy(p, v);
		return;
	}
	push_down(p);
	int mid = (l + r) >> 1;
	if(L <= mid){
		add(L, R, v, l, mid, p << 1);
	}
	if(R > mid){
		add(L, R, v, mid+1, r, p << 1 | 1);
	}
	push_up(p);
}

void change(int L, int R, int v, int l, int r, int p){
	if(L <= l && r <= R){
		changeLazy(p, v);
		return;
	}
	push_down(p);
	int mid = (l + r) >> 1;
	if(L <= mid){
		change(L, R, v, l, mid, p << 1);
	}
	if(R > mid){
		change(L, R, v, mid+1, r, p << 1 | 1);
	}
	push_up(p);
}

int query(int L, int R, int l, int r, int p){
	if(L <= l && r <= R){
		return tr[p];
	}
	push_down(p);
	int ans = LONG_LONG_MIN;
	int mid = (l + r) >> 1;
	if(L <= mid){
		ans = max(ans, query(L, R, l, mid, p << 1));
	}
	if(R > mid){
		ans = max(ans, query(L, R, mid+1, r, p << 1 | 1));
	}
	return ans;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	int n, q;
	cin >> n >> q;
	foreach(1, n, i){
		cin >> a[i];
	}
	build(1, n, 1);
	foreach(1, q, i){
		int opt, l, r, x;
		cin >> opt >> l >> r;
		if(opt == 3){
			cout << query(l, r, 1, n, 1) << '\n';
		}
		else{
			cin >> x;
			if(opt == 1){
				change(l, r, x, 1, n, 1);
			}
			else{
				add(l, r, x, 1, n, 1);
			}
		}
	}
}