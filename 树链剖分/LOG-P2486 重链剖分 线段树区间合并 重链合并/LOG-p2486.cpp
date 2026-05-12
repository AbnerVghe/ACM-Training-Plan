#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 1e5+7;
int arr[N], sz[N], fa[N], dep[N], son[N], top[N], dfn[N], seg[N];
int cntD;
int sum[N << 2], lcolor[N << 2], rcolor[N << 2], lazy[N << 2];
vector<int> p[N];
int n;

void dfs1(int x, int f){
    dep[x] = dep[f] + 1;
    fa[x] = f;
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
    dfn[x] = ++cntD;
    seg[cntD] = x;
    if(!son[x]) return;
    dfs2(son[x], t);
    for(auto v: p[x]){
        if(v == fa[x] || v == son[x]) continue;
        dfs2(v, v);
    }
}

void push_up(int p){
    sum[p] = sum[p << 1] + sum[p << 1 | 1];
    if(rcolor[p << 1] == lcolor[p << 1 | 1]){
        sum[p]--;
    }
    lcolor[p] = lcolor[p << 1];
    rcolor[p] = rcolor[p << 1 | 1];
}

void build(int l, int r, int p){
    if(l == r){
        sum[p] = 1;
        lcolor[p] = rcolor[p] = arr[seg[l]];
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, p << 1);
    build(mid+1, r, p << 1 | 1);
    push_up(p);
}

void update(int p, int v){
    sum[p] = 1;
    lcolor[p] = rcolor[p] = v;
    lazy[p] = v;
}

void push_down(int p){
    if(lazy[p]){
        update(p << 1, lazy[p]);
        update(p << 1 | 1, lazy[p]);
        lazy[p] = 0;
    }
}

void setVal(int L, int R, int v, int l, int r, int p){
    if(L <= l && r <= R){
        update(p, v);
        return;
    }
    int mid = (l + r) >> 1;
    push_down(p);
    if(L <= mid) setVal(L, R, v, l, mid, p << 1);
    if(R > mid) setVal(L, R, v, mid+1, r, p << 1 | 1);
    push_up(p);
}

int querySum(int L, int R, int l, int r, int p){
    if(L <= l && r <= R){
        return sum[p];
    }
    push_down(p);
    int mid = (l + r) >> 1;
    if(R <= mid) return querySum(L, R, l, mid, p << 1);
    if(L > mid) return querySum(L, R, mid+1, r, p << 1 | 1);
    int ans = querySum(L, R, l, mid, p << 1) + querySum(L, R, mid+1, r, p << 1 | 1);
    if(rcolor[p << 1] == lcolor[p << 1 | 1]){
        ans--;
    }
    return ans;
}

int queryColor(int x, int l, int r, int p){
    if(l == r){
        return lcolor[p];
    }
    int mid = (l + r) >> 1;
    push_down(p);
    if(x <= mid) return queryColor(x, l, mid, p << 1);
    else return queryColor(x, mid+1, r, p << 1 | 1);
}

void setPath(int x, int y, int v){
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        setVal(dfn[top[x]], dfn[x], v, 1, n, 1);
        x = fa[top[x]];
    }
    setVal(min(dfn[x], dfn[y]), max(dfn[x], dfn[y]), v, 1, n, 1);
}

int queryPath(int x, int y){
    int ans = 0;
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        ans += querySum(dfn[top[x]], dfn[x], 1, n, 1);
        if(queryColor(dfn[top[x]], 1, n, 1) == queryColor(dfn[fa[top[x]]], 1, n, 1)){
            ans--;
        }
        x = fa[top[x]];
    }
    ans += querySum(min(dfn[x], dfn[y]), max(dfn[x], dfn[y]), 1, n, 1);
    return ans;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int m;
    cin >> n >> m;
    foreach(1, n, i){
        cin >> arr[i];
    }
    foreach(1, n-1, i){
        int u, v;
        cin >> u >> v;
        p[u].push_back(v);
        p[v].push_back(u);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    build(1, n, 1);
    while(m--){
        char opt;
        int a, b, c;
        cin >> opt >> a >> b;
        if(opt == 'C'){
            cin >> c;
            setPath(a, b, c);
        }
        else{
            cout << queryPath(a, b) << '\n';
        }
    }
}