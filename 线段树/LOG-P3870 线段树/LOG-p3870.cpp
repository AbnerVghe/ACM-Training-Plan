#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 1e5+7;
int opened[4*N], lazy[4*N];

void update(int p, int tag,int n){
    lazy[p] ^= tag;
    if(tag) opened[p] = n - opened[p];
}

void push_down(int p, int ln, int rn){
    if(lazy[p]){
        update(p << 1, lazy[p], ln);
        update(p << 1 | 1, lazy[p], rn);
        lazy[p] = 0;
    }
}

void push_up(int p){
    opened[p] = opened[p << 1] + opened[p << 1 | 1];
}

void change(int L, int R, int l, int r, int p){
    if(L <= l && r <= R){
        update(p, 1, r-l+1);
        return;
    }
    int mid = (l + r) >> 1;
    push_down(p, mid-l+1, r-mid);
    if(L <= mid){
        change(L, R, l, mid, p << 1);
    }
    if(R > mid){
        change(L, R, mid+1, r, p << 1 | 1);
    }
    push_up(p);
}

int query(int L, int R, int l, int r, int p){
    if(L <= l && r <= R){
        return opened[p];
    }
    int mid = (l + r) >> 1;
    push_down(p, mid-l+1, r-mid);
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
    cin.tie(0), cout.tie(0);

    int n, m;
    cin >> n >> m;
    foreach(1, m, i){
        int c, a, b;
        cin >> c >> a >> b;
        if(c) cout << query(a, b, 1, n, 1) << '\n';
        else change(a, b, 1, n, 1);
    }
}