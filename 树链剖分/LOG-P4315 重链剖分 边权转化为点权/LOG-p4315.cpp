#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 1e5+7;
int sz[N], dep[N], fa[N], son[N], top[N], dfn[N];
int cnt;
vector<int> p[N];
int maxN[N << 2];
bool change[N << 2];
int lazyChange[N << 2], lazyAdd[N << 2];
int n;
struct Edge{
    int u, v, w;
}edges[N];


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
    maxN[p] = max(maxN[p << 1], maxN[p << 1 | 1]);
}

void updateAdd(int p, int v){
    maxN[p] += v;
    lazyAdd[p] += v;
}

void updateChange(int p, int v){
    maxN[p] = v;
    lazyAdd[p] = 0;
    change[p] = 1;
    lazyChange[p] = v;
}

void push_down(int p){
    if(change[p]){
        updateChange(p << 1, lazyChange[p]);
        updateChange(p << 1 | 1, lazyChange[p]);
        change[p] = 0;
    }
    if(lazyAdd[p]){
        updateAdd(p << 1, lazyAdd[p]);
        updateAdd(p << 1 | 1, lazyAdd[p]);
        lazyAdd[p] = 0;
    }
}

void setVal(int L, int R, int v, int l, int r, int p){
    if(L <= l && r <= R){
        updateChange(p, v);
        return;
    }
    int mid = (l + r) >> 1;
    push_down(p);
    if(L <= mid) setVal(L, R, v, l, mid, p << 1);
    if(R > mid) setVal(L, R, v, mid+1, r, p << 1 | 1);
    push_up(p);
}

void addVal(int L, int R, int v, int l, int r, int p){
    if(L <= l && r <= R){
        updateAdd(p, v);
        return;
    }
    int mid = (l + r) >> 1;
    push_down(p);
    if(L <= mid) addVal(L, R, v, l, mid, p << 1);
    if(R > mid) addVal(L, R, v, mid+1, r, p << 1 | 1);
    push_up(p);
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

void setPath(int x, int y, int v){
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        setVal(dfn[top[x]], dfn[x], v, 1, n, 1);
        x = fa[top[x]];
    }
    setVal(min(dfn[x], dfn[y])+1, max(dfn[x], dfn[y]), v, 1, n, 1);
}

void addPath(int x, int y, int v){
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        addVal(dfn[top[x]], dfn[x], v, 1, n, 1);
        x = fa[top[x]];
    }
    addVal(min(dfn[x], dfn[y])+1, max(dfn[x], dfn[y]), v, 1, n, 1);
}

void setEdge(int x, int y, int v){
    int tmp = max(dfn[x], dfn[y]);
    setVal(tmp, tmp, v, 1, n, 1);
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

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    foreach(1, n-1, i){
        int u, v, w;
        cin >> u >> v >> w;
        edges[i] = {u, v, w};
        p[u].push_back(v);
        p[v].push_back(u);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    foreach(1, n-1, i){
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        setEdge(u, v, w);
    }
    while(1){
        string opt;
        cin >> opt;
        if(opt == "Stop") break;
        if(opt == "Change"){
            int k, w;
            cin >> k >> w;
            int u = edges[k].u, v = edges[k].v;
            setEdge(u, v, w);
        }
        else if(opt == "Max"){
            int u, v;
            cin >> u >> v;
            cout << queryPathMax(u, v) << '\n';
        }
        else{
            int u, v, w;
            cin >> u >> v >> w;
            if(opt == "Cover"){
                setPath(u, v, w);
            }
            else{
                addPath(u, v, w);
            }
        }
    }
}