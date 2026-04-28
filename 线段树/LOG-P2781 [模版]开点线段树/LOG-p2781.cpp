#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 80010;//需要的空间大约为2*m*logn，其中m为操作次数
int cnt;
int sum[N], lazy[N], Left[N], Right[N];//Left Right相当于lp和rp

void push_up(int p, int l, int r){
    sum[p] = sum[l] + sum[r];
}

void update(int p, int v, int n){
    sum[p] += v * n;
    lazy[p] += v;
}

void push_down(int p, int ln, int rn){
    if(lazy[p]){
        if(!Left[p]) Left[p] = ++cnt;//若无左儿子则开辟空间
        if(!Right[p]) Right[p] = ++cnt;//同理
        update(Left[p], lazy[p], ln);
        update(Right[p], lazy[p], rn);
        lazy[p] = 0;
    }
}

void change(int L, int R, int v, int l, int r, int p){
    if(L <= l && r <= R){
        update(p, v, r-l+1);
        return;
    }
    int mid = (l + r) >> 1;
    push_down(p, mid-l+1, r-mid);
    if(L <= mid){//如果不得不去左边
        if(!Left[p]) Left[p] = ++cnt;
        change(L, R, v, l, mid, Left[p]);
    }
    if(R > mid){//如果不得不去右边
        if(!Right[p]) Right[p] = ++cnt;
        change(L, R, v, mid+1, r, Right[p]);
    }
    push_up(p, Left[p], Right[p]);
}

int query(int L, int R, int l, int r, int p){
    if(L <= l && r <= R){
        return sum[p];
    }
    int mid = (l + r) >> 1;
    push_down(p, mid-l+1, r-mid);
    int ans = 0;
    if(L <= mid){
        if(Left[p]) ans += query(L, R, l, mid, Left[p]);//左边有才加
    }
    if(R > mid){
        if(Right[p]) ans += query(L, R, mid+1, r, Right[p]);//右边有才加
    }
    return ans;  
}

void clear(){
    foreach(0, cnt+1, i){
        Left[i] = Right[i] = lazy[i] = sum[i] = 0;
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n, m;
    cin >> n >> m;
    cnt = 1;
    while(m--){
        int opt, l, r;
        cin >> opt >> l >> r;
        if(opt == 1){
            int k;
            cin >> k;
            change(l, r, k, 1, n, 1);
        }
        else{
            cout << query(l, r, 1, n, 1) << '\n';
        }
    }
}