#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 1e5+7, LM = 20;
const int T = N * 20;
int n, m, slen;
int arr[N], sorted[N];
int root[N], Left[T], Right[T], sz[T], cnt;
int dep[N], st[N][30];
vector<int> p[N];

int insert(int, int, int, int);

int Rank(int val){
    return lower_bound(sorted+1, sorted+slen+1, val) - sorted;
}

void dfs(int x, int fa){
    st[x][0] = fa;
    dep[x] = dep[fa] + 1;
    root[x] = insert(Rank(arr[x]), 1, n, root[fa]);
    foreach(1, LM, j){
        st[x][j] = st[st[x][j-1]][j-1];
    }
    for(auto v: p[x]){
        if(v == fa) continue;
        dfs(v, x);
    }
}

int getLca(int x, int y){
    if(dep[x] < dep[y]) swap(x, y);
    int t = dep[x] - dep[y];
    foreach_sub(LM, 0, j){
        if((t>>j)&1){
            x = st[x][j];
        }
    }
    if(x == y) return x;
    foreach_sub(LM, 0, j){
        if(st[x][j] != st[y][j]){
            x = st[x][j], y = st[y][j];
        }
    }
    return st[x][0];
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
        if(x <= mid) Left[rt] = insert(x, l, mid, Left[rt]);
        else Right[rt] = insert(x, mid+1, r, Right[rt]);
    }
    return rt;
}

int query(int k, int l, int r, int u, int v, int lca, int lcaFa){
    if(l == r) return l;
    int lsz = sz[Left[u]] + sz[Left[v]] - sz[Left[lca]] - sz[Left[lcaFa]];
    int mid = (l + r) >> 1;
    if(k <= lsz){
        return query(k, l, mid, Left[u], Left[v], Left[lca], Left[lcaFa]);
    }
    else return query(k-lsz, mid+1, r, Right[u], Right[v], Right[lca], Right[lcaFa]);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    foreach(1, n, i){
        int tmp;
        cin >> tmp;
        arr[i] = sorted[i] = tmp;
    }
    sort(sorted+1, sorted+n+1);
    slen = unique(sorted+1, sorted+n+1) - sorted - 1;
    foreach(1, n-1, i){
        int x, y;
        cin >> x >> y;
        p[x].push_back(y);
        p[y].push_back(x);
    }
    root[0] = build(1, n);
    dfs(1, 0);
    int lastAns = 0;
    while(m--){
        int u, v, k;
        cin >> u >> v >> k;
        u ^= lastAns;
        int lca = getLca(u, v);
        int lcaFa = st[lca][0];
        int x = sorted[query(k, 1, n, root[u], root[v], root[lca], root[lcaFa])];
        cout << x << '\n';
        lastAns = x;
    }
}