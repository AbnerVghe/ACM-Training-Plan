#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 5e4+7;
struct Info{
    int maxN, minN, lprofit, rprofit;
}tree[N << 2];
int lazy[N << 2];
int sz[N], dep[N], fa[N], top[N], son[N], dfn[N], seg[N];
int n, arr[N];
int cnt;
vector<int> p[N];

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
    seg[cnt] = x;
    if(!son[x]) return;
    dfs2(son[x], t);
    for(auto v: p[x]){
        if(v == fa[x] || v == son[x]) continue;
        dfs2(v, v);
    }
}

Info merge(Info L, Info R){
    Info newInfo;
    newInfo.maxN = max(L.maxN, R.maxN);
    newInfo.minN = min(L.minN, R.minN);
    newInfo.lprofit = max(max(L.lprofit, R.lprofit), R.maxN-L.minN);
    newInfo.rprofit = max(max(L.rprofit, R.rprofit), L.maxN-R.minN);
    return newInfo;
}

void push_up(int p){
    tree[p] = merge(tree[p << 1], tree[p << 1 | 1]);
}

void update(int p, int v){
    tree[p].maxN += v;
    tree[p].minN += v;
    lazy[p] += v;
}

void push_down(int p){
    if(lazy[p]){
        update(p << 1, lazy[p]);
        update(p << 1 | 1, lazy[p]);
       lazy[p] = 0;
    }
}

void build(int l, int r, int p){
    if(l == r){
        int price = arr[seg[l]];
        tree[p] = {price, price, 0, 0};
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, p << 1);
    build(mid+1, r, p << 1 | 1);
    push_up(p);
}

void add(int L, int R, int v, int l, int r, int p){
    if(L <= l && r <= R){
        update(p, v);
        return;
    }
    int mid = (l + r) >> 1;
    push_down(p);
    if(L <= mid) add(L, R, v, l, mid, p << 1);
    if(R > mid) add(L, R, v, mid+1, r, p << 1 | 1);
    push_up(p);
}

Info query(int L, int R, int l, int r, int p){
    if(L <= l && r <= R){
        return tree[p];
    }
    int mid = (l + r) >> 1;
    push_down(p);
    Info ans = {-INF, INF, 0, 0};
    if(L <= mid) ans = merge(ans, query(L, R, l, mid, p << 1));
    if(R > mid) ans = merge(ans, query(L, R, mid+1, r, p << 1 | 1));
    return ans;
}

int compute(int x, int y, int v){
    int tmpx = x, tmpy = y;
    Info xpath, ypath;
    xpath = ypath = {-INF, INF, 0, 0};
    while(top[x] != top[y]){
        if(dep[top[x]] <= dep[top[y]]){
            ypath = merge(query(dfn[top[y]], dfn[y], 1, n, 1), ypath);
            y = fa[top[y]];
        }
        else{
            xpath = merge(query(dfn[top[x]], dfn[x], 1, n, 1), xpath);
            x = fa[top[x]];
        }
    }
    if(dep[x] <= dep[y]){
        ypath = merge(query(dfn[x], dfn[y], 1, n, 1), ypath);
    }
    else xpath = merge(query(dfn[y], dfn[x], 1, n, 1), xpath);
    int ans = max(max(xpath.rprofit, ypath.lprofit), ypath.maxN-xpath.minN);
    x = tmpx, y = tmpy;
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        add(dfn[top[x]], dfn[x], v, 1, n, 1);
        x = fa[top[x]];
    }
    add(min(dfn[x], dfn[y]), max(dfn[x], dfn[y]), v, 1, n, 1);
    return ans;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    foreach(1, n, i) cin >> arr[i];
    foreach(1, n-1, i){
        int x, y;
        cin >> x >> y;
        p[x].push_back(y);
        p[y].push_back(x);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    build(1, n, 1);
    int q;
    cin >> q;
    while(q--){
        int a, b, v;
        cin >> a >> b >> v;
        cout << compute(a, b, v) << '\n';
    }
}