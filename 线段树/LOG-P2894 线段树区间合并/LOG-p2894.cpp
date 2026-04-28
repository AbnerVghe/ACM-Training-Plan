#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 5e4+7;
int len[N << 2], pre[N << 2], suf[N << 2], lazy[N << 2], changeTo[N << 2];

void push_up(int p, int ln, int rn){
    int l = p << 1, r = p << 1 | 1;
    len[p] = max(max(len[l], len[r]), suf[l]+pre[r]);
    pre[p] = pre[l] < ln ? pre[l] : (pre[l]+pre[r]);
    suf[p] = suf[r] < rn ? suf[r] : (suf[l]+suf[r]);
}

void update(int p, int v, int n){
    len[p] = pre[p] = suf[p] = v == 0 ? n : 0;
    lazy[p] = 1;
    changeTo[p] = v;
}

void push_down(int p, int ln, int rn){
    if(lazy[p]){
        update(p << 1, changeTo[p], ln);
        update(p << 1 | 1, changeTo[p], rn);
        lazy[p] = 0;
    }
}

void change(int L, int R, int v, int l, int r, int p){
    if(l == r){
        update(p, v, r-l+1);
        return;
    }
    int mid = (l + r) >> 1;
    push_down(p, mid-l+1, r-mid);
    if(L <= mid){
        change(L, R, v, l, mid, p << 1);
    }
    if(R > mid){
        change(L, R, v, mid+1, r, p << 1 | 1);
    }
    push_up(p, mid-l+1, r-mid);
}

void build(int l, int r, int p){
    lazy[p] = 0;
    if(l == r){
        len[p] = pre[p] = suf[p] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, p << 1);
    build(mid+1, r, p << 1 | 1);
    push_up(p, mid-l+1, r-mid);
}

int query(int L, int R, int x, int l, int r, int p){
    if(l == r) return l;
    int mid = (l + r) >> 1;
    push_down(p, mid-l+1, r-mid);
    int lp = p << 1, rp = p << 1 | 1;
    if(len[lp] >= x){
        return query(L, R, x, l, mid, p << 1);
    }
    if(suf[lp]+pre[rp] >= x){
        return mid - suf[lp] + 1;
    }
    return query(L, R, x, mid+1, r, p << 1 | 1);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n, m;
    cin >> n >> m;
    build(1, n, 1);
    while(m--){
        int opt;
        cin >> opt;
        if(opt == 1){
            int x;
            cin >> x;
            if(len[1] < x){
                cout << "0\n";
            }
            else{
                int L = query(1, n, x, 1, n, 1);
                int R = L + x - 1;
                cout << L << '\n';
                change(L, R, 1, 1, n, 1);
            }
        }
        else{
            int x, y;
            cin >> x >> y;
            change(x, x+y-1, 0, 1, n, 1);
        }
    }
}