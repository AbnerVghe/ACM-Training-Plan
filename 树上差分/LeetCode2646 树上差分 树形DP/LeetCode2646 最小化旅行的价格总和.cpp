#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 60, L = 8;
int cnt[N], st[N][10], dep[N];
int dp[N][2], cost[N];//0:不降，1:降
vector<int> p[N];

void init(int n){
    foreach(0, n, i){
        cnt[i] = 0;
        p[i].clear();
        foreach(0, L, j) st[i][j] = 0;
        foreach(0, 1, j) dp[i][j] = 0;
    }
}

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

void update(int x, int fa){
    for(auto v: p[x]){
        if(v == fa) continue;
        update(v, x);
        cnt[x] += cnt[v];
    }
}

void dfs2(int x, int fa){
    dp[x][0] = cost[x];
    dp[x][1] = cost[x] / 2;
    for(auto v: p[x]){
        if(v == fa) continue;
        dfs2(v, x);
        dp[x][0] += min(dp[v][0], dp[v][1]);
        dp[x][1] += dp[v][0];
    }
}

class Solution {
public:
    int minimumTotalPrice(int n, vector<vector<int>>& edges, vector<int>& price, vector<vector<int>>& trips) {
        init(n);
        for(auto edge: edges){
            int u = edge[0]+1, v = edge[1]+1;
            p[u].push_back(v);
            p[v].push_back(u);
        }
        dfs(1, 0);
        for(auto trip: trips){
            int u = trip[0]+1, v = trip[1]+1;
            int lca = getLca(u, v);
            cnt[u]++, cnt[v]++;
            cnt[lca]--, cnt[st[lca][0]]--;
        }
        update(1, 0);
        foreach(1, n, i){
            cost[i] = cnt[i]*price[i-1];
        }
        dfs2(1, 0);
        return min(dp[1][0], dp[1][1]);
    }
};