#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 2e5+7;
const int T = N*22;
int a[N], Sort[N], slen;
int root[N], Left[T], Right[T], cnt;
int sz[T];//排名范围内收集了多少数字

int Rank(int val){
    return lower_bound(Sort+1, Sort+slen+1, val) - Sort;
}

int build(int l, int r){
    int rt = ++cnt;
    sz[rt] = 0;
    if(l < r){
        int mid = (l + r) >> 1;
        Left[rt] = build(l, mid);
        Right[rt] = build(mid+1, r);
    }
    return rt;
}

int insert(int x, int l, int r, int p){
    int rt = ++cnt;
    Left[rt] = Left[p];
    Right[rt] = Right[p];
    sz[rt] = sz[p] + 1;
    if(l < r){
        int mid = (l + r) >> 1;
        if(x <= mid){
            Left[rt] = insert(x, l, mid, Left[rt]);
        }
        else Right[rt] = insert(x, mid+1, r, Right[rt]);
    }
    return rt;
}

//查询：利用新版本[u]-老版本[v]
//返回第k小的数字离散后排名多少
int query(int k, int l, int r, int u, int v){
    if(l == r) return l;
    int lsz = sz[Left[v]] - sz[Left[u]];
    int mid = (l + r) >> 1;
    if(lsz >= k){
        return query(k, l, mid, Left[u], Left[v]);
    }
    else return query(k-lsz, mid+1, r, Right[u], Right[v]);
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
        Sort[i] = a[i];
    }
    sort(Sort+1, Sort+n+1);
    slen = unique(Sort+1, Sort+n+1) - (Sort+1);
    root[0] = build(1, slen);
    foreach(1, n, i){
        int x = Rank(a[i]);
        root[i] = insert(x, 1, slen, root[i-1]);
    }
    while(m--){
        int l, r, k;
        cin >> l >> r >> k;
        cout << Sort[query(k, 1, slen, root[l-1], root[r])] << '\n';
    }
}
