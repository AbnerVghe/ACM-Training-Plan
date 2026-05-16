#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)//删掉这个和下面便无403
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 1e5+7;
const int T = N * 70;
int arr[N], Left[T], Right[T], cnt;
ll sum[T], addTag[T];
int t = 0;
int root[N];

int build(int l, int r){
    int rt = ++cnt;
    if(l == r){
        sum[rt] = arr[l];
    }
    else{
        int mid = (l + r) >> 1;
        Left[rt] = build(l, mid);
        Right[rt] = build(mid+1, r);
        sum[rt] = sum[Left[rt]] + sum[Right[rt]];
    }
    return rt;
}

int add(int L, int R, int v, int l, int r, int p){
    int rt = ++cnt;
    int a = max(L, l), b = min(R, r);
    sum[rt] = sum[p] + v * (b-a+1);
    Left[rt] = Left[p];
    Right[rt] = Right[p];
    addTag[rt] = addTag[p];
    if(L <= l && r <= R){
        addTag[rt] += v;
    }
    else{
        int mid = (l + r) >> 1;
        if(L <= mid) Left[rt] = add(L, R, v, l, mid, Left[rt]);
        if(R > mid) Right[rt] = add(L, R, v, mid+1, r, Right[rt]);
    }
    return rt;
}

ll query(int L, int R, ll addHis, int l, int r, int p){
    if(L <= l && r <= R){
        return sum[p] + addHis * (r-l+1);
    }
    int mid = (l + r) >> 1;
    ll ans = 0;
    if(L <= mid) ans += query(L, R, addHis+addTag[p], l, mid, Left[p]);
    if(R > mid) ans += query(L, R, addHis+addTag[p], mid+1, r, Right[p]);
    return ans;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++){//被迫修改
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
                cout << query(l, r, 0, 1, n, root[t]) << '\n';
            }
            else{
                int z;
                cin >> z;
                cout << query(l, r, 0, 1, n, root[z]) << '\n';
            }
        }
    }
}