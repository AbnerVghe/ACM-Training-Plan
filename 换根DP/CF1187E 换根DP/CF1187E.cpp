#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 2e5+7;
int sz[N], dp[N];
vector<int> p[N];
int n;

void dfs(int x, int fa){
    sz[x] = 1;
    for(auto v: p[x]){
        if(v == fa) continue;
        dfs(v, x);
        sz[x] += sz[v];
    }
    dp[1] += sz[x];
}

void dfs2(int x, int fa){
    for(auto v: p[x]){
        if(v == fa) continue;
        dp[v] = dp[x] + n - 2*sz[v];
        dfs2(v, x);
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    foreach(1, n-1, i){
        int u, v;
        cin >> u >> v;
        p[u].push_back(v);
        p[v].push_back(u);
    }
    dfs(1, 0);
    dfs2(1, 0);
    int maxn = 0;
    foreach(1, n, i){
        maxn = max(maxn, dp[i]);
    }
    cout << maxn;
}