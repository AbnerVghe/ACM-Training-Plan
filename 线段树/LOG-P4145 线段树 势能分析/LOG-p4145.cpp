#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 1e5+7;
int sum[4*N], maxn[4*N], a[N];

void push_up(int p){
    sum[p] = sum[p << 1] + sum[p << 1 | 1];
    maxn[p] = max(maxn[p << 1], maxn[p << 1 | 1]);
}

void build(int l, int r, int p){
    if(l == r){
        sum[p] = maxn[p] = a[l];
        return;
    }

    int mid = (l + r) >> 1;
    build(l, mid, p << 1);
    build(mid+1, r, p << 1 | 1);
    push_up(p);
}

void setSqrt(int L, int R, int l, int r, int p){
    if(l == r){
        int res = sqrt(maxn[p]);
        sum[p] = maxn[p] = res;
        return;
    }
    
    int mid = (l + r) >> 1;
    if(L <= mid && maxn[p << 1] > 1){
        setSqrt(L, R, l, mid, p << 1);
    }
    if(R > mid && maxn[p << 1 | 1] > 1){
        setSqrt(L, R, mid+1, r, p << 1 | 1);
    }
    push_up(p);
}

int query(int L, int R, int l, int r, int p){
    if(L <= l && r <= R){
        return sum[p];
    }
    int mid = (l + r) >> 1;
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

    int n;
    cin >> n;
    foreach(1, n, i){
        cin >> a[i];
    }
    build(1, n, 1);
    int m;
    cin >> m;
    foreach(1, m, i){
        int opt, l, r;
        cin >> opt >> l >> r;
        if(l > r) swap(l, r);
        if(opt == 0){
            setSqrt(l, r, 1, n, 1);
        }
        else{
            cout << query(l, r, 1, n, 1) << '\n';
        }
    }
}