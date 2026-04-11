#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

typedef pair<int, int> pii;

const int N = 1e5;
int lazy[4*N], sum[4*N], a[N];

void push_up(int p){//汇总信息
	sum[p] = sum[p << 1] + sum[p << 1 | 1];
}

void update(int p, int v, int n){//懒住了
	sum[p] += v * n;
	lazy[p] += v;
}

void push_down(int p, int ln, int rn){//下发懒标记
	if(lazy[p]){
		update(p << 1, lazy[p], ln);//更新左边懒标记
		update(p << 1 | 1, lazy[p], rn);//更新右边懒标记
		lazy[p] = 0;//下发完毕，清除懒标记
	}
}

void build(int l, int r, int p){//建树
	if(l == r){
		sum[p] = a[l];
		return;
	}

	int mid = (l + r) >> 1;
	build(l, mid, p << 1);
	build(mid+1, r, p << 1 | 1);
	push_up(p);

	lazy[p] = 0;
}

void add(int L, int R, int v, int l, int r, int p){//区间修改
	if(L <= l && r <= R){//全包，则直接更新懒标记
		update(p, v, r-l+1);
		return;
	}
	//否则，要往下戳
	int mid = (l + r) >> 1;
	push_down(p, mid - l + 1, r - mid);//下发懒标记
	if(L <= mid){//修改左边
		add(L, R, v, l, mid, p << 1);
	}
	if(R > mid){//修改右边
		add(L, R, v, mid+1, r, p << 1 | 1);
	}
	push_up(p);//汇总
}

int query(int L, int R, int l, int r, int p){
	if(L <= l && r <= R){
		return sum[p];
	}

	int mid = (l + r) >> 1;
	push_down(p, mid - l + 1, r - mid);
	int ans = 0;
	if(L <= mid){
		ans += query(L, R, l, mid, p << 1);
	}
	if(R > mid){
		ans += query(L, R, mid+1, r, p << 1 | 1);
	}
	return ans;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	int n, m;
	cin >> n >> m;
	foreach(1, n, i){
		cin >> a[i];
	}
	build(1, n, 1);
	foreach(1, m, i){
		int opt, x, y;
		cin >> opt >> x >> y;
		if(opt == 1){
			int k;
			cin >> k;
			add(x, y, k, 1, n, 1);
		}
		else{
			cout << query(x, y, 1, n, 1) << '\n';
		}
	}
}