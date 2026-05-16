#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 1e5+7;
const int T = N * 70;
int cnt, root[N], sum[T], lazy[T], Left[T], Right[T], arr[N];
int t = 0;

int clone(int p){
    int rt = ++cnt;
    Left[rt] = Left[p];
    Right[rt] = Right[p];
    sum[rt] = sum[p];
    lazy[rt] = lazy[p];
    return rt;
}

void push_up(int p){
    sum[p] = sum[Left[p]] + sum[Right[p]];
}

void update(int p, int v, int n){
    sum[p] += v * n;
    lazy[p] += v;
}

void push_down(int p, int ln, int rn){
    if(lazy[p]){
        Left[p] = clone(Left[p]);
        Right[p] = clone(Right[p]);
        update(Left[p], lazy[p], ln);
        update(Right[p], lazy[p], rn);
        lazy[p] = 0;
    }
}

int build(int l, int r){
    int rt = ++cnt;
    lazy[rt] = 0;
    if(l == r){
        sum[rt] = arr[l];
    }
    else{
        int mid = (l + r) >> 1;
        Left[rt] = build(l, mid);
        Right[rt] = build(mid+1, r);
        push_up(rt); 
    }
    return rt;
}

int add(int L, int R, int v, int l, int r, int p){
    int rt = clone(p);
    if(L <= l && r <= R){
        update(rt, v, r-l+1);
    }
    else{
        int mid = (l + r) >> 1;
        push_down(rt, mid-l+1, r-mid);
        if(L <= mid){
            Left[rt] = add(L, R, v, l, mid, Left[rt]);
        }
        if(R > mid){
            Right[rt] = add(L, R, v, mid+1, r, Right[rt]);
        }
        push_up(rt);
    }
    return rt;
}

int query(int L, int R, int l, int r, int p){
    //无需在push_down以外新建节点
    if(L <= l && r <= R){
        return sum[p];
    }
    int mid = (l + r) >> 1;
    push_down(p, mid-l+1, r-mid);
    int ans = 0;
    if(L <= mid) ans += query(L, R, l, mid, Left[p]);
    if(R > mid) ans += query(L, R, mid+1, r, Right[p]);
    return ans;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n, m;
    cin >> n >> m;
    foreach(1, n, i){
        cin >> arr[i];    
    }
    root[0] = build(1, n);
    while(m--){
        char opt;
        int l, r, d;
        cin >> opt;
        if(opt == 'B'){
            cin >> t;
        }
        else{
            cin >> l >> r;
            if(opt == 'C'){
                cin >> d; 
                root[t+1] = add(l, r, d, 1, n, root[t]);
                t++;                   
            }
            else if(opt == 'Q'){
                cout << query(l, r, 1, n, root[t]) << '\n';
            }
            else{
                int z;
                cin >> z;
                cout << query(l, r, 1, n, root[z]) << '\n';
            }
        }
    }
}