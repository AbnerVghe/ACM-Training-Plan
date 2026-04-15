#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

const int N = 310, M = 310;
int dp[N][M];
int dfn[N], sz[N], val[N], s[N];
int cntD;
vector<int> p[N];
int n, m;

void dfs(int x){
    int id = ++cntD;
    dfn[x] = id;
    sz[id] = 1;
    val[id] = s[x];
    for(auto v: p[x]){
        dfs(v);
        sz[id] += sz[dfn[v]];
    }
    /*foreach(1, m, i){
        dp[id][i] = max(dp[id+sz[id]][i], dp[id+1][i-1]+val[id]);
    }*/
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;
    foreach(1, n, i){
        int u, w;
        cin >> u >> w;
        p[u].push_back(i);
        s[i] = w;
    }
    dfs(0);
    foreach_sub(n+1, 2, i) foreach(1, m, j){
        dp[i][j] = max(dp[i+sz[i]][j], val[i]+dp[i+1][j-1]);
    }
    cout << dp[2][m] << '\n';
}