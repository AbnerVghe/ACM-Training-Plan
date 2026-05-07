#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 1e5+7, L = 20;
int st[N][25], dep[N], num[N];
int ans;
int m;
vector<int> p[N];

void dfs(int x, int fa){
    dep[x] = dep[fa] + 1;
    st[x][0] = fa;
    foreach(1, L, j){
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
    foreach_sub(L, 0, j){
        if((t >> j)&1) x = st[x][j];
    }
    if(x == y) return x;
    foreach_sub(L, 0, j){
        if(st[x][j] != st[y][j]){
            x = st[x][j], y = st[y][j];
        }
    }
    return st[x][0];
}

void dfs2(int x, int fa){
    for(auto v: p[x]){
        if(v == fa) continue;
        dfs2(v, x);
        int w = 0 + num[v];
        if(w == 0) ans += m;
        else if(w == 1) ans += 1;

        num[x] += num[v];
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n;
    cin >> n >> m;
    foreach(1, n-1, i){
        int a, b;
        cin >> a >> b;
        p[a].push_back(b);
        p[b].push_back(a);
    }
    dfs(1, 0);
    foreach(1, m, i){
        int a, b;
        cin >> a >> b;
        int lca = getLca(a, b);
        num[a]++, num[b]++;
        num[lca] -= 2;
    }
    dfs2(1, 0);
    cout << ans;
}