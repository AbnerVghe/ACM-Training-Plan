#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 8e4+7, L = 20;
const int T = N * 110;
int st[N][25], dep[N];
int arr[N], sorted[N], slen;
int root[N], Left[T], Right[T], sz[T], cnt;
int treeHead[N], setSz[N];
vector<int> p[N];

int Rank(int val){
    return lower_bound(sorted+1, sorted+slen+1, val) - sorted;
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
    int mid = (l + r) >> 1;
    int lsz = sz[Left[u]] + sz[Left[v]] - sz[Left[lca]] - sz[Left[lcaFa]];
    if(lsz >= k){
        return query(k, l, mid, Left[u], Left[v], Left[lca], Left[lcaFa]);
    }
    else return query(k-lsz, mid+1, r, Right[u], Right[v], Right[lca], Right[lcaFa]);
}

int getLca(int x, int y){
    if(dep[x] < dep[y]) swap(x, y);
    int t = dep[x] - dep[y];
    foreach_sub(L, 0, j){
        if((t>>j)&1) x = st[x][j];
    }
    if(x == y) return x;
    foreach_sub(L, 0, j){
        if(st[x][j] != st[y][j]){
            x = st[x][j], y = st[y][j];
        }
    }
    return st[x][0];
}

int queryKth(int x, int y, int k){
    int lca = getLca(x, y);
    int lcaFa = st[lca][0];
    int i = query(k, 1, slen, root[x], root[y], root[lca], root[lcaFa]);
    return sorted[i];
}

void dfs(int x, int f, int th){
    treeHead[x] = th;
    st[x][0] = f;
    setSz[th]++;
    dep[x] = dep[f] + 1;
    foreach(1, L, j){
        st[x][j] = st[st[x][j-1]][j-1];
    }
    root[x] = insert(Rank(arr[x]), 1, slen, root[f]);
    for(auto v: p[x]){
        if(v == f) continue;
        dfs(v, x, th);
    }
}

void add(int x, int y){
    p[x].push_back(y);
    p[y].push_back(x);
    int fx = treeHead[x];
    int fy = treeHead[y];
    if(setSz[fx] >= setSz[fy]){
        dfs(y, x, fx);
    }
    else dfs(x, y, fy);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int Tt;
    cin >> Tt;
        int n, m, q;
        cin >> n >> m >> q;
        cnt = 0;
        foreach(1, n, i){
            p[i].clear();
            treeHead[i] = setSz[i] = 0;
        }
        foreach(1, n, i){
            cin >> arr[i];
            sorted[i] = arr[i];
        }
        sort(sorted+1, sorted+n+1);
        slen = unique(sorted+1, sorted+n+1) - sorted - 1;
        root[0] = build(1, slen);
        foreach(1, m, i){
            int x, y;
            cin >> x >> y;
            p[x].push_back(y);
            p[y].push_back(x);
        }
        foreach(1, n, i){
            if(!treeHead[i]){
                dfs(i, 0, i);
            }
        }
        int lastAns = 0;
        while(q--){
            char opt;
            int x, y, k;
            cin >> opt >> x >> y;
            x ^= lastAns, y ^= lastAns;
            if(opt == 'Q'){
                cin >> k;
                k ^= lastAns;
                lastAns = queryKth(x, y, k);
                cout << lastAns << '\n';
            }
            else{
                add(x, y);
            }
    }
}