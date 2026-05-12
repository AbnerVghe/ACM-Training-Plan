#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 1e5+7;
int sz[N], fa[N], dep[N], top[N], son[N], dfn[N];
int cnt;
int sum[N << 2], lazy[N << 2];
vector<int> p[N];
int n;

void dfs1(int x, int f){
    fa[x] = f;
    dep[x] = dep[f] + 1;
    sz[x] = 1;
    for(auto v: p[x]){
        if(v == f) continue;
        dfs1(v, x);
        sz[x] += sz[v];
        if(!son[x] || sz[son[x]] < sz[v]){
            son[x] = v;
        }
    }
}

void dfs2(int x, int t){
    top[x] = t;
    dfn[x] = ++cnt;
    if(!son[x]) return;
    dfs2(son[x], t);
    for(auto v: p[x]){
        if(v == fa[x] || v == son[x]) continue;
        dfs2(v, v);
    }
}

void push_up(int p){
    sum[p] = sum[p << 1] + sum[p << 1 | 1];
}

void update(int p, int v, int n){
    sum[p] += v * n;
    lazy[p] += v;
}

void push_down(int p, int ln, int rn){
    if(lazy[p]){
        update(p << 1, lazy[p], ln);
        update(p << 1 | 1, lazy[p], rn);
        lazy[p] = 0;
    }
}

void add(int L, int R, int v, int l, int r, int p){
    if(L <= l && r <= R){
        update(p, v, r-l+1);
        return;
    }
    int mid = (l + r) >> 1;
    push_down(p, mid-l+1, r-mid);
    if(L <= mid) add(L, R, v, l, mid, p << 1);
    if(R > mid) add(L, R, v, mid+1, r, p << 1 | 1);
    push_up(p);
}

int querySum(int x, int l, int r, int p){
    if(l == r){
        return sum[p];
    }
    int mid = (l + r) >> 1;
    push_down(p, mid-l+1, r-mid);
    if(x <= mid) return querySum(x, l, mid, p << 1);
    else return querySum(x, mid+1, r, p << 1 | 1);
}

void addPath(int x, int y, int v){
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        add(dfn[top[x]], dfn[x], v, 1, n, 1);
        x = fa[top[x]];
    }
    //不加LCA
    add(min(dfn[x], dfn[y])+1, max(dfn[x], dfn[y]), v, 1, n, 1);
}

int queryEdge(int x, int y){
    return querySum(max(dfn[x], dfn[y]), 1, n, 1);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int m;
    cin >> n >> m;
    foreach(1, n-1, i){
        int u, v;
        cin >> u >> v;
        p[u].push_back(v);
        p[v].push_back(u);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    while(m--){
        char opt;
        int u, v;
        cin >> opt >> u >> v;
        if(opt == 'P'){
            addPath(u, v, 1);
        }
        else{
            cout << queryEdge(u, v) << '\n';
        }
    }
}