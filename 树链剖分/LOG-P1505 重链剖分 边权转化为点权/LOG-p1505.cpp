#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 2e5+7;
struct Edge{
    int u, v, w;
}edges[N];
int sz[N], dep[N], fa[N], son[N], top[N], dfn[N];
int cnt;
int sum[N << 2], minN[N << 2], maxN[N << 2];
bool lazy[N << 2];
int cntE, head[N], to[N << 1], nxt[N << 1];
//vector<int> p[N];
int n;

void addEdge(int u, int v){
    nxt[++cntE] = head[u];
    to[cntE] = v;
    head[u] = cntE;
}

void dfs1(int x, int f){
    fa[x] = f;
    dep[x] = dep[f] + 1;
    sz[x] = 1;
    for(int e = head[x]; e; e = nxt[e]){
        int v = to[e];
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
    for(int e = head[x]; e; e = nxt[e]){
        int v = to[e];
        if(v == fa[x] || v == son[x]) continue;
        dfs2(v, v);
    }
}

void push_up(int p){
    sum[p] = sum[p << 1] + sum[p << 1 | 1];
    maxN[p] = max(maxN[p << 1], maxN[p << 1 | 1]);
    minN[p] = min(minN[p << 1], minN[p << 1 | 1]);
}

void updateReverse(int p){
    sum[p] *= -1;
    maxN[p] *= -1, minN[p] *= -1;
    swap(maxN[p], minN[p]);
    lazy[p] ^= 1;
}

void push_down(int p){
    if(lazy[p]){
        updateReverse(p << 1);
        updateReverse(p << 1 | 1);
        lazy[p] = 0;
    }
}

void setVal(int x, int v, int l, int r, int p){
    if(l == r){
        sum[p] = maxN[p] = minN[p] = v;
        return;
    }
    int mid = (l + r) >> 1;
    push_down(p);
    if(x <= mid) setVal(x, v, l, mid, p << 1);
    else setVal(x, v, mid+1, r, p << 1 | 1);
    push_up(p);
}

void setReverse(int L, int R, int l, int r, int p){
    if(L <= l && r <= R){
        updateReverse(p);
        return;
    }
    int mid = (l + r) >> 1;
    push_down(p);
    if(L <= mid) setReverse(L, R, l, mid, p << 1);
    if(R > mid) setReverse(L, R, mid+1, r, p << 1 | 1);
    push_up(p);
}

int querySum(int L, int R, int l, int r, int p){
    if(L <= l && r <= R){
        return sum[p];
    }
    int mid = (l + r) >> 1;
    push_down(p);
    int ans = 0;
    if(L <= mid) ans += querySum(L, R, l, mid, p << 1);
    if(R > mid) ans += querySum(L, R, mid+1, r, p << 1 | 1);
    return ans;
}

int queryMax(int L, int R, int l, int r, int p){
    if(L <= l && r <= R){
        return maxN[p];
    }
    int mid = (l + r) >> 1;
    push_down(p);
    int ans = LONG_LONG_MIN;
    if(L <= mid) ans = max(ans, queryMax(L, R, l, mid, p << 1));
    if(R > mid) ans = max(ans, queryMax(L, R, mid+1, r, p << 1 | 1));
    return ans;
}

int queryMin(int L, int R, int l, int r, int p){
    if(L <= l && r <= R){
        return minN[p];
    }
    int mid = (l + r) >> 1;
    push_down(p);
    int ans = LONG_LONG_MAX;
    if(L <= mid) ans = min(ans, queryMin(L, R, l, mid, p << 1));
    if(R > mid) ans = min(ans, queryMin(L, R, mid+1, r, p << 1 | 1));
    return ans;
}

void setEdge(int x, int y, int v){
    setVal(max(dfn[x], dfn[y]), v, 1, n, 1);
}

void reversePath(int x, int y){
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        setReverse(dfn[top[x]], dfn[x], 1, n, 1);
        x = fa[top[x]];
    }
    setReverse(min(dfn[x], dfn[y])+1, max(dfn[x], dfn[y]), 1, n, 1);
}

int queryPathSum(int x, int y){
    int ans = 0;
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        ans += querySum(dfn[top[x]], dfn[x], 1, n, 1);
        x = fa[top[x]];
    }
    ans += querySum(min(dfn[x], dfn[y])+1, max(dfn[x], dfn[y]), 1, n, 1);
    return ans;
}

int queryPathMax(int x, int y){
    int ans = LONG_LONG_MIN;
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        ans = max(ans, queryMax(dfn[top[x]], dfn[x], 1, n, 1));
        x = fa[top[x]];
    }
    ans = max(ans, queryMax(min(dfn[x], dfn[y])+1, max(dfn[x], dfn[y]), 1, n, 1));
    return ans;
}

int queryPathMin(int x, int y){
    int ans = LONG_LONG_MAX;
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        ans = min(ans, queryMin(dfn[top[x]], dfn[x], 1, n, 1));
        x = fa[top[x]];
    }
    ans = min(ans, queryMin(min(dfn[x], dfn[y])+1, max(dfn[x], dfn[y]), 1, n, 1));
    return ans;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    foreach(1, n-1, i){
        int u, v, w;
        cin >> u >> v >> w;
        u++, v++;
        addEdge(u, v);
        addEdge(v, u);
        edges[i] = {u, v, w};
    }
    dfs1(1, 0);
    dfs2(1, 0);
    foreach(1, n-1, i){
        int x = edges[i].u, y = edges[i].v, w = edges[i].w;
        setEdge(x, y, w);
    }
    int m;
    cin >> m;
    while(m--){
        string opt;
        int x, y;
        cin >> opt >> x >> y;
        if(opt == "C"){
            int u = edges[x].u, v = edges[x].v;
            setEdge(u, v, y);
        }
        else if(opt == "N"){
            reversePath(++x, ++y);
        }
        else if(opt == "SUM"){
            cout << queryPathSum(++x, ++y) << '\n';
        }
        else if(opt == "MAX"){
            cout << queryPathMax(++x, ++y) << '\n';
        }
        else cout << queryPathMin(++x, ++y) << '\n';
    }
}