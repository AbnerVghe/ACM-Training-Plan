#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 3e5+7;
const int T = N * 30;
int root[N], Left[T], Right[T], sum[T], cntt;
int dfn[N], cntd, sz[N], dep[N];
vector<int> p[N];
int n, depth;

int build(int l, int r){
    int rt = ++cntt;
    sum[rt] = 0;
    if(l < r){
        int mid = (l + r) >> 1;
        Left[rt] = build(l, mid);
        Right[rt] = build(mid+1, r);
    }
    return rt;
}

int update(int x, int v, int l, int r, int p){
    int rt = ++cntt;
    Left[rt] = Left[p];
    Right[rt] = Right[p];
    sum[rt] = sum[p] + v;
    if(l < r){
        int mid = (l + r) >> 1;
        if(x <= mid) Left[rt] = update(x, v, l, mid, Left[rt]);
        else Right[rt] = update(x, v, mid+1, r, Right[rt]);
    }
    return rt;
}

int query(int L, int R, int l, int r, int u, int v){
    if(L <= l && r <= R){
        return sum[v] - sum[u];
    }
    int mid = (l + r) >> 1;
    int ans = 0;
    if(L <= mid) ans += query(L, R, l, mid, Left[u], Left[v]);
    if(R > mid) ans += query(L, R, mid+1, r, Right[u], Right[v]);
    return ans;
}

void dfs1(int x, int fa){
    dep[x] = dep[fa] + 1;
    sz[x] = 1;
    for(auto v: p[x]){
        if(v == fa) continue;
        dfs1(v, x);
        sz[x] += sz[v];
    }
}

void dfs2(int x, int fa){
    dfn[x] = ++cntd;
    root[cntd] = update(dep[x], sz[x]-1, 1, depth, root[cntd-1]);
    for(auto v: p[x]){
        if(v == fa) continue;
        dfs2(v, x);
    }
}

int compute(int x, int k){
    int ans = (sz[x] - 1) * min(dep[x]-1, k);
    ans += query(dep[x]+1, dep[x]+k, 1, depth, root[dfn[x]-1], root[dfn[x]+sz[x]-1]);
    return ans;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int q;
    cin >> n >> q;
    foreach(1, n-1, i){
        int u, v;
        cin >> u >> v;
        p[u].push_back(v);
        p[v].push_back(u);
    }
    dfs1(1, 0);
    depth = dep[1];
    foreach(2, n, i){
        depth = max(depth, dep[i]);
    }
    root[0] = build(1, n);
    dfs2(1, 0);
    while(q--){
        int x, k;
        cin >> x >> k;
        cout << compute(x, k) << '\n';
    }
}