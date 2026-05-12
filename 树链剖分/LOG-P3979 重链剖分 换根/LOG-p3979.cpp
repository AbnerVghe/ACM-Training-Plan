#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 1e5+7;
int arr[N], sz[N], fa[N], dep[N], son[N], top[N], dfn[N], seg[N], cnt;
int n;
int minN[N << 2];
int lazy[N << 2];
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

void push_up(int p){
    minN[p] = min(minN[p << 1], minN[p << 1 | 1]);
}

void update(int p, int v){
    minN[p] = v;
    lazy[p] = v;
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
        minN[p] = arr[seg[l]];
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, p << 1);
    build(mid+1, r, p << 1 | 1);
    push_up(p);
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

int findSon(int root, int x){
    while(top[root] != top[x]){
        if(fa[top[root]] == x) return top[root];
        root = fa[top[root]];
    }
    return son[x];
}

int queryTree(int root, int x){
    if(root == x){
        return minN[1];
    }
    if(dfn[root] < dfn[x] || dfn[root] >= dfn[x] + sz[x]){
        return queryMin(dfn[x], dfn[x]+sz[x]-1, 1, n, 1);
    }
    int xson = findSon(root, x);
    int ans = queryMin(1, dfn[xson]-1, 1, n, 1);
    if(dfn[xson] + sz[xson] - 1 < n){
        ans = min(ans, queryMin(dfn[xson] + sz[xson], n, 1, n, 1));
    }
    return ans;
}

void setPath(int x, int y, int v){
    while(top[x] != top[y]){
        if(dep[top[x] < dep[top[y]]]) swap(x, y);
        setVal(dfn[top[x]], dfn[x], v, 1, n, 1);
        x = fa[top[x]];
    }
    setVal(min(dfn[x], dfn[y]), max(dfn[x], dfn[y]), v, 1, n, 1);
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
    foreach(1, n, i){
        cin >> arr[i];
    }
    dfs1(1, 0);
    dfs2(1, 0);
    build(1, n, 1);
    int root;
    cin >> root;
    while(m--){
        int opt;
        cin >> opt;
        if(opt == 1){
            int id;
            cin >> id;
            root = id;
        }
        else if(opt == 2){
            int x, y, z;
            cin >> x >> y >> z;
            setPath(x, y, z);
        }
        else{
            int x;
            cin >> x;
            cout << queryTree(root, x) << '\n';
        }
    }

}