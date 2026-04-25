#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 1e5+7;
int sum[4*N], lazy[4*N], a[N], b[N];

void push_up(int p){
    sum[p] = sum[p << 1] + sum[p << 1 | 1];
}

void update(int p, int v, int n){
    sum[p] += v * n;
    lazy[p] += v;
}

void push_down(int p, int ln, int rn){
    if(lazy[p]){
        update(p << 1, lazy[p], ln);
        update(p << 1 | 1, lazy[p], rn);
        lazy[p] = 0;
    }
}

void addVal(int L, int R, int v, int l, int r, int p){
    if(L <= l && r <= R){
        update(p, v, r-l+1);
        return;
    }
    int mid = (l + r) >> 1;
    push_down(p, mid-l+1, r-mid);
    if(L <= mid){
        addVal(L, R, v, l, mid, p << 1);
    }
    if(R > mid){
        addVal(L, R, v, mid+1, r, p << 1 | 1);
    }
    push_up(p);
}

int query(int L, int R, int l, int r, int p){
    if(L <= l && r <= R){
        return sum[p];
    }
    int mid = (l + r) >> 1;
    int ans = 0;
    push_down(p, mid-l+1, r-mid);
    if(L <= mid){
        ans += query(L, R, l, mid, p << 1);
    }
    if(R > mid){
        ans += query(L, R, mid+1, r, p << 1 | 1);
    }
    return ans;
}

void build(int l, int r, int p){
    if(l > r) return;
    if(l == r){
        sum[p] = b[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, p << 1);
    build(mid+1, r, p << 1 | 1);
    push_up(p);
    lazy[p] = 0;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n, m;
    cin >> n >> m;
    foreach(1, n, i){
        cin >> a[i];
    }
    foreach(1, n, i){
        b[i] = a[i] - a[i-1];
    }
    build(1, n, 1);
    while(m--){
        int opt;
        cin >> opt;
        if(opt == 1){
            int l, r, K, D, E;
            cin >> l >> r >> K >> D;
            E = K + D*(r-l);
            addVal(l, l, K, 1, n, 1);
            if(l < r) addVal(l+1, r, D, 1, n, 1);
            if(r+1 <= n) addVal(r+1, r+1, -E, 1, n, 1);
        }
        else{
            int p;
            cin >> p;
            cout << query(1, p, 1, n, 1) << '\n';
        }
    }
}