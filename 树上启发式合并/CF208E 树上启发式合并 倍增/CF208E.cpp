#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 1e5+7, L = 20;
bool root[N];
int son[N], dep[N], sz[N];
vector<int> p[N];
struct Qs{
    int id, k;
};
vector<Qs> qss[N];
vector<int> depSet[N];
int n;
int ans[N];
int st[N][25];

void dfs1(int x, int f){
    dep[x] = dep[f] + 1;
    sz[x] = 1;
    st[x][0] = f;
    foreach(1, L, j){
        st[x][j] = st[st[x][j-1]][j-1];
    }
    for(auto v: p[x]){
        dfs1(v, x);
        sz[x] += sz[v];
        if(!son[x] || sz[son[x]] < sz[v]){
            son[x] = v;
        }
    }
}

void effect(int x){
    depSet[dep[x]].push_back(x);
    for(auto v: p[x]){
        effect(v);
    }
}

void cancel(int x){
    depSet[dep[x]].clear();
    for(auto v: p[x]){
        cancel(v);
    }
}

int getSize(int deep){
    if(deep > n) return 0;
    return depSet[deep].size();
}

void dfs2(int x, bool keep){
    for(auto v: p[x]){
        if(v == son[x]) continue;
        dfs2(v, 0);
    }
    if(son[x]){
        dfs2(son[x], 1);
    }
    depSet[dep[x]].push_back(x);
    for(auto v: p[x]){
        if(v == son[x]) continue;
        effect(v);
    }
    for(auto qs: qss[x]){
        int id = qs.id, k = qs.k;
        ans[id] = getSize(dep[x]+k);
    }
    if(!keep) cancel(x);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    foreach(1, n, i){
        int fa;
        cin >> fa;
        if(fa){
            p[fa].push_back(i);
        }
        else root[i] = 1;
    }
    foreach(1, n, i){
        if(root[i]) dfs1(i, 0);
    }
    int m;
    cin >> m;
    foreach(1, m, i){
        int x, k;
        cin >> x >> k;
        foreach_sub(L, 0, j){
            if((k>>j)&1) x = st[x][j];
        }
        if(x) qss[x].push_back({i, k});
        else ans[i] = 1;
    }
    foreach(1, n, i){
        if(root[i]) dfs2(i, 0);
    }
    foreach(1, m, i){
        cout << ans[i]-1 << ' ';
    }
}