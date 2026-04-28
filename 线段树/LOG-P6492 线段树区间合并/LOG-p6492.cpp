#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 2e5+7;
char a[N];
int len[N << 2], pre[N << 2], suf[N << 2];

void push_up(int l, int r, int p){
    int lp = p << 1, rp = p << 1 | 1;
    len[p] = max(len[lp], len[rp]);
    pre[p] = pre[lp], suf[p] = suf[rp];
    int mid = (l + r) >> 1;
    if(a[mid] != a[mid+1]){
        len[p] = max(len[p], suf[lp]+pre[rp]);
        pre[p] = (pre[lp] < mid-l+1) ? pre[lp] : (pre[lp]+pre[rp]);
        suf[p] = (suf[rp] < r-mid) ? suf[rp] : (suf[lp]+suf[rp]);
    }
}

void change(int x, int l, int r, int p){
    if(l == r){
        if(a[l] == 'L') a[l] = 'R';
        else a[l] = 'L';
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid) change(x, l, mid, p << 1);
    else change(x, mid+1, r, p << 1 | 1);
    push_up(l, r, p);
}

void build(int l, int r, int p){
    if(l == r){
        len[p] = pre[p] = suf[p] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, p << 1);
    build(mid+1, r, p << 1 | 1);
    push_up(l, r, p);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n, q;
    cin >> n >> q;
    foreach(1, n, i) a[i] = 'L';
    build(1, n, 1);
    while(q--){
        int x;
        cin >> x;
        change(x, 1, n, 1);
        cout << len[1] << '\n';
    }
}