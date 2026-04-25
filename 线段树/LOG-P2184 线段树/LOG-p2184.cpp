#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 1e5+7;
int st[4*N], ed[4*N];

void push_up(int p){
    st[p] = st[p << 1] + st[p << 1 | 1];
    ed[p] = ed[p << 1] + ed[p << 1 | 1];
}

void addVal(int x, int type, int l, int r, int p){
    if(l == r){
        if(type == 0) st[p]++;
        else ed[p]++;
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid){
        addVal(x, type, l, mid, p << 1);
    }
    else addVal(x, type, mid+1, r, p << 1 | 1);
    push_up(p);
}

int query(int L, int R, int type, int l, int r, int p){
    if(L > R) return 0;
    if(L <= l && r <= R){
        int ans = (type == 0) ? st[p] : ed[p];
        return ans;
    }
    int mid = (l + r) >> 1;
    int ans = 0;
    if(L <= mid){
        ans += query(L, R, type, l, mid, p << 1);
    }
    if(R > mid){
        ans += query(L, R, type, mid+1, r, p << 1 | 1);
    }
    return ans;
}

signed main(){
    ios::sync_with_stdio(0);
    cout.tie(0), cin.tie(0);

    int n, m;
    cin >> n >> m;
    foreach(1, m, i){
        int q, l, r;
        cin >> q >> l >> r;
        if(q == 1){
            addVal(l, 0, 1, n, 1);
            addVal(r, 1, 1, n, 1);
        }
        else{
            int ans = query(1, r, 0, 1, n, 1) - query(1, l-1, 1, 1, n, 1);
            cout << ans << '\n';
        }
    }
}