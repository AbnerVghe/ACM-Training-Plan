#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 5e4+7;
int pre[N << 2], suf[N << 2], stk[N], cnt = 0;
void push_up(int l, int r, int p){
    pre[p] = pre[p << 1];
    suf[p] = suf[p << 1 | 1];
    int mid = (l + r) >> 1;
    if(pre[p] >= mid-l+1) pre[p] += pre[p << 1 | 1];
    if(suf[p] >= r-mid) suf[p] += suf[p << 1];
}

void build(int l, int r, int p){
    if(l == r){
        pre[p] = suf[p] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, p << 1);
    build(mid+1, r, p << 1 | 1);
    push_up(l, r, p);
}

void change(int x, int v, int l, int r, int p){
    if(l == r){
        pre[p] = suf[p] = v;
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid) change(x, v, l, mid, p << 1);
    else change(x, v, mid+1, r, p << 1 | 1);
    push_up(l, r, p);
}

int query(int x, int l, int r, int p){
    if(l == r) return pre[p];
    int mid = (l + r) >> 1;
    if(x <= mid){//在左边
        if(x >= mid-suf[p << 1]+1){//被左边的后缀包住
            return suf[p << 1] + pre[p << 1 | 1];
        }
        else return query(x, l, mid, p << 1);
    }
    else{
        if(x <= mid+pre[p << 1 | 1]){
            return suf[p << 1] + pre[p << 1 | 1];
        }
        else return query(x, mid+1, r, p << 1 | 1);
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n, m;
    cin >> n >> m;
    build(1, n, 1);
    while(m--){
        char opt;
        int x;
        cin >> opt;
        if(opt == 'D'){
            cin >> x;
            stk[++cnt] = x;
            change(x, 0, 1, n, 1);
        }
        else if(opt == 'R'){
            x = stk[cnt--];
            change(x, 1, 1, n, 1);
        }
        else{
            cin >> x;
            cout << query(x, 1, n, 1) << '\n';
        }
    }
}