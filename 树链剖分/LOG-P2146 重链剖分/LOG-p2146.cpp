#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 1e5+7;
int fa[N], sz[N], dep[N], son[N], top[N], dfn[N];
int cntD;
int lazy[N << 2], sum[N << 2];
bool change[N << 2];
vector<int> p[N];
int n;

void dfs1(int x, int f){
    fa[x] = f;
    dep[x] = dep[f] + 1;
    sz[x] = 1;
    for(auto v: p[x]){
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
    if(!son[x]) return;
    dfs2(son[x], t);
    for(auto v: p[x]){
        if(v == son[x]) continue;
        dfs2(v, v);
    }
}

void push_up(int p){
    sum[p] = sum[p << 1] + sum[p << 1 | 1];
}

void update(int p, int v, int n){
    sum[p] = n * v;
    lazy[p] = v;
    change[p] = 1;
}

void push_down(int p, int ln, int rn){
    if(change[p]){
        update(p << 1, lazy[p], ln);
        update(p << 1 | 1, lazy[p], rn);
        change[p] = 0;
    }
}

void setVal(int L, int R, int v, int l, int r, int p){
    if(L <= l && r <= R){
        update(p, v, r-l+1);
        return;
    }
    int mid = (l + r) >> 1;
    push_down(p, mid-l+1, r-mid);
    if(L <= mid) setVal(L, R, v, l, mid, p << 1);
    if(R > mid) setVal(L, R, v, mid+1, r, p << 1 | 1);
    push_up(p);
}

int querySum(int L, int R, int l, int r, int p){
    if(L <= l && r <= R){
        return sum[p];
    }
    int mid = (l + r) >> 1;
    push_down(p, mid-l+1, r-mid);
    int ans = 0;
    if(L <= mid) ans += querySum(L, R, l, mid, p << 1);
    if(R > mid) ans += querySum(L, R, mid+1, r, p << 1 | 1);
    return ans;
}

void setPath(int x, int y, int v){
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        setVal(dfn[top[x]], dfn[x], v, 1, n, 1);
        x = fa[top[x]];
    }
    setVal(min(dfn[x], dfn[y]), max(dfn[x], dfn[y]), v, 1, n, 1);
}

void setSubtree(int x, int v){
    setVal(dfn[x], dfn[x]+sz[x]-1, v, 1, n, 1);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    foreach(2, n, i){
        int tmp;
        cin >> tmp;
        tmp++;
        p[tmp].push_back(i);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    int q;
    cin >> q;
    while(q--){
        string opt;
        int x;
        cin >> opt >> x;
        x++;
        int nowState = querySum(dfn[x], dfn[x], 1, n, 1);
        if(opt == "install"){
            if(nowState){
                cout << 0 << '\n';
            }
            else{
                int pre = sum[1];
                setPath(1, x, 1);
                int cur = sum[1];
                cout << cur - pre << '\n';
            }
        }
        else{
            if(!nowState){
                cout << 0 << '\n';
            }
            else{
                int pre = sum[1];
                setSubtree(x, 0);
                int cur = sum[1];
                cout << pre - cur << '\n';
            }
        }
    }
}