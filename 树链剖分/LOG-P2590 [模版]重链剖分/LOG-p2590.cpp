#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 3e4+7;
int arr[N], fa[N], sz[N], dep[N], son[N], top[N], dfn[N], seg[N];
int cntD;
int sum[N << 2], maxN[N << 2];
vector<int> p[N];
int n;

void dfs1(int x, int f){
    sz[x] = 1;
    fa[x] = f;
    dep[x] = dep[f] + 1;
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
    maxN[p] = max(maxN[p << 1], maxN[p << 1 | 1]);
}

void build(int l, int r, int p){
    if(l == r){
        sum[p] = maxN[p] = arr[seg[l]];
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, p << 1);
    build(mid+1, r, p << 1 | 1);
    push_up(p);
}

void update(int p, int v){
    sum[p] = v;
    maxN[p] = v;
}

void setVal(int x, int v, int l, int r, int p){
    if(l == r){
        update(p, v);
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid) setVal(x, v, l, mid, p << 1);
    else setVal(x, v, mid+1, r, p << 1 | 1);
    push_up(p);
}

int queryMax(int L, int R, int l, int r, int p){
    if(L <= l && r <= R){
        return maxN[p];
    }
    int mid = (l + r) >> 1;
    int ans = -3e4-7;
    if(L <= mid) ans = max(ans, queryMax(L, R, l, mid, p << 1));
    if(R > mid) ans = max(ans, queryMax(L, R, mid+1, r, p << 1 | 1));
    return ans;
}

int querySum(int L, int R, int l, int r, int p){
    if(L <= l && r <= R){
        return sum[p];
    }
    int mid = (l + r) >> 1;
    int ans = 0;
    if(L <= mid) ans += querySum(L, R, l, mid, p << 1);
    if(R > mid) ans += querySum(L, R, mid+1, r, p << 1 | 1);
    return ans;
}

void setPath(int x, int v){
    setVal(dfn[x], v, 1, n, 1);
}

int queryPathMax(int x, int y){
    int ans = -3e4-7;
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        ans = max(ans, queryMax(dfn[top[x]], dfn[x], 1, n, 1));
        x = fa[top[x]];
    }
    ans = max(ans, queryMax(min(dfn[x], dfn[y]), max(dfn[x], dfn[y]), 1, n, 1));
    return ans;
}

int queryPathSum(int x, int y){
    int ans = 0;
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        ans += querySum(dfn[top[x]], dfn[x], 1, n, 1);
        x = fa[top[x]];
    }
    ans += querySum(min(dfn[x], dfn[y]), max(dfn[x], dfn[y]), 1, n, 1);
    return ans;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    foreach(1, n-1, i){
        int a, b;
        cin >> a >> b;
        p[a].push_back(b);
        p[b].push_back(a);
    }
    foreach(1, n, i){
        cin >> arr[i];
    }
    dfs1(1, 0);
    dfs2(1, 0);
    build(1, n, 1);
    int q;
    cin >> q;
    while(q--){
        string opt; int u, v;
        cin >> opt >> u >> v;
        if(opt == "CHANGE"){
            setPath(u, v);
        }
        else if(opt == "QMAX"){
            cout << queryPathMax(u, v) << '\n';
        }
        else{
            cout << queryPathSum(u, v) << '\n';
        }
    }
}