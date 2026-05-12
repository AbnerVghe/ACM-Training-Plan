#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 1e5+7;
int arr[N], fa[N], dep[N], sz[N], son[N], top[N], dfn[N], seg[N], cntD;
vector<int> p[N];
int sum[N << 2], lazy[N << 2];
int MOD;
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
    sum[p] = (sum[p << 1] + sum[p << 1 | 1]) % MOD;
}

void update(int p, int v, int n){
    sum[p] = (sum[p] + v*n)%MOD;
    lazy[p] = (lazy[p] + v)%MOD;
}

void push_down(int p, int ln, int rn){
    if(lazy[p]){
        update(p << 1, lazy[p], ln);
        update(p << 1 | 1, lazy[p], rn);
        lazy[p] = 0;
    }
}

void build(int l, int r, int p){
    if(l == r){
        sum[p] = arr[seg[l]] % MOD;
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, p << 1);
    build(mid+1, r, p << 1 | 1);
    push_up(p);
}

void add(int L, int R, int v, int l, int r, int p){
    if(L <= l && r <= R){
        update(p, v, r-l+1);
        return;
    }
    int mid = (l + r) >> 1;
    push_down(p, mid-l+1, r-mid);
    if(L <= mid){
        add(L, R, v, l, mid, p << 1);
    }
    if(R > mid){
        add(L, R, v, mid+1, r, p << 1 | 1);
    }
    push_up(p);
}

int query(int L, int R, int l, int r, int p){
    if(L <= l && r <= R){
        return sum[p];
    }
    int mid = (l + r) >> 1;
    push_down(p, mid-l+1, r-mid);
    int ans = 0;
    if(L <= mid){
        ans = (ans + query(L, R, l, mid, p << 1))%MOD;
    }
    if(R > mid){
        ans = (ans + query(L, R, mid+1, r, p << 1 | 1))%MOD;
    }
    return ans;
}

void pathAdd(int x, int y, int v){
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        add(dfn[top[x]], dfn[x], v, 1, n, 1);
        x = fa[top[x]];
    }
    add(min(dfn[x], dfn[y]), max(dfn[x], dfn[y]), v, 1, n, 1);
}

void subtreeAdd(int x, int v){
    add(dfn[x], dfn[x]+sz[x]-1, v, 1, n, 1);
}

int pathSum(int x, int y){
    int ans = 0;
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        ans = (ans + query(dfn[top[x]], dfn[x], 1, n, 1))%MOD;
        x = fa[top[x]];
    }
    ans = (ans + query(min(dfn[x], dfn[y]), max(dfn[x], dfn[y]), 1, n, 1))%MOD;
    return ans;
}

int subtreeSum(int x){
    return query(dfn[x], dfn[x]+sz[x]-1, 1, n, 1);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int m, root;
    cin >> n >> m >> root >> MOD;
    foreach(1, n, i) cin >> arr[i];
    foreach(1, n-1, i){
        int u, v;
        cin >> u >> v;
        p[u].push_back(v);
        p[v].push_back(u);
    }
    dfs1(root, 0);
    dfs2(root, 0);
    build(1, n, 1);
    foreach(1, m, i){
        int opt, x, y, z;
        cin >> opt >> x;
        if(opt == 1){
            cin >> y >> z;
            pathAdd(x, y, z);
        }
        else if(opt == 2){
            cin >> y;
            cout << pathSum(x, y) << '\n';
        }
        else if(opt == 3){
            cin >> z;
            subtreeAdd(x, z);
        }
        else{
            cout << subtreeSum(x) << '\n';
        }
    }
}