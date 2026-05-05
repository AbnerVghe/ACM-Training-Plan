#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 1e4+7, M = 2e4+7;
int lca[M];
vector<pair<int, int>> p[N];
vector<pair<int, int>> qss[N];
bool vis[N];
int fa[N];
int Cnt[N][30];

void init(int n){
    foreach(1, n, i){
        fa[i] = i;
        qss[i].clear();
        vis[i] = 0;
        p[i].clear();
    }
}

int find(int x){
    if(fa[x] != x){
        fa[x] = find(fa[x]);
    }
    return fa[x];
}

void add(int x, int y){//add x to y
    int fx = find(x), fy = find(y);
    if(fx != fy){
        fa[fx] = fy;
    }
}

void dfs(int x, int fa, int w){
    vis[x] = 1;
    if(fa){
        foreach(1, 26, i){
            Cnt[x][i] = Cnt[fa][i];
        }
        Cnt[x][w]++;
    }
    else{
        foreach(1, 26, i){
            Cnt[x][i] = 0;
        }
    }
    for(auto e: p[x]){
        int v = e.first, w = e.second;
        if(v == fa) continue;
        dfs(v, x, w);
        add(v, x);
    }
    for(auto qs: qss[x]){
        int v = qs.first, id = qs.second;
        if(v == x) lca[id] = x;
        else{
            if(!vis[v]) continue;
            lca[id] = find(v);
        }
    }
}

void getLca(int n, vector<vector<int>> quries){
    int m = quries.size();
    foreach(1, m, i){
        int a = quries[i-1][0]+1, b = quries[i-1][1]+1;
        qss[a].push_back({b, i});
        qss[b].push_back({a, i});
    }
    dfs(1, 0, 0);
}

class Solution {
public:
    vector<int> minOperationsQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        init(n);
        for(auto edge: edges){
            int u = edge[0]+1, v = edge[1]+1, w = edge[2];
            p[u].push_back({v, w});
            p[v].push_back({u, w});
        }
        getLca(n, queries);
        int m = queries.size();
        vector<int> ans(m);
        foreach(1, m, i){
            int a = queries[i-1][0]+1, b = queries[i-1][1]+1, c = lca[i];
            int maxCnt = 0, allCnt = 0;
            foreach(1, 26, i){
                int wCnt = Cnt[a][i] + Cnt[b][i] - 2*Cnt[c][i];
                maxCnt = max(maxCnt, wCnt);
                allCnt += wCnt;
            }
            ans[i-1] = allCnt - maxCnt;
        }
        return ans;
    }
};