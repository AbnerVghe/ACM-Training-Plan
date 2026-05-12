#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 1e5+7, K = 30;
int sum[N][K], dp[N][K], a[N];
vector<int> p[N];
int n, k;

void dfs(int x, int fa){
    sum[x][0] = a[x];
    for(auto v: p[x]){
        if(v == fa) continue;
        dfs(v, x);
        foreach(1, k, j){
            sum[x][j] += sum[v][j-1];
        }
    }
}

void dfs2(int x, int fa){
    for(auto v: p[x]){
        if(v == fa) continue;
        dp[v][0] = a[v];
        dp[v][1] = a[x] + sum[v][1];
        foreach(2, k, j){
            dp[v][j] = sum[v][j] + dp[x][j-1] - sum[v][j-2];
        }
        dfs2(v, x);
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> k;
    foreach(1, n-1, i){
        int u, v;
        cin >> u >> v;
        p[u].push_back(v);
        p[v].push_back(u);
    }
    foreach(1, n, i){
        cin >> a[i];
    }
    dfs(1, 0);
    foreach(0, k, i){
        dp[1][i] = sum[1][i];
    }
    dfs2(1, 0);
    foreach(1, n, i){
        int tmp = 0;
        foreach(0, k, j){
            tmp += dp[i][j];
        }
        cout << tmp << '\n';
    }
}