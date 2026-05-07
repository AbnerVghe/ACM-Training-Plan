#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 5e4+7, L = 20;
int st[N][25], dep[N], num[N];
vector<int> p[N];
int maxAns;

void dfs(int x, int fa){
    if(fa){
        dep[x] = dep[fa] + 1;
    }
    else dep[x] = 1;
    st[x][0] = fa;

    foreach(1, L, j){
        st[x][j] = st[st[x][j-1]][j-1];
    }
    for(auto v: p[x]){
        if(v == fa) continue;
        dfs(v, x);
    }
}

int lca(int x, int y){
    if(dep[x] < dep[y]) swap(x, y);
    int t = dep[x] - dep[y];
    foreach_sub(L, 0, j){
        if((t>>j) & 1) x = st[x][j];
    }
    if(x == y) return x;
    foreach_sub(L, 0, j){
        if(st[x][j] != st[y][j]){
            x = st[x][j], y = st[y][j];
        }
    }
    return st[x][0];
}

void find(int x, int fa){
    int ans = 0;
    for(auto v: p[x]){
        if(v == fa) continue;
        find(v, x);
        ans += num[v];
    }
    num[x] += ans;
    maxAns = max(maxAns, num[x]);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n, k;
    cin >> n >> k;
    foreach(1, n-1, i){
        int x, y;
        cin >> x >> y;
        p[x].push_back(y);
        p[y].push_back(x);
    }
    dfs(1, 0);
    while(k--){
        int s, t;
        cin >> s >> t;
        int LCA = lca(s, t);
        //cout << LCA << '\n';
        num[s]++, num[t]++;
        num[LCA]--, num[st[LCA][0]]--;
    }
    find(1, 0);
    cout << maxAns << '\n';
}