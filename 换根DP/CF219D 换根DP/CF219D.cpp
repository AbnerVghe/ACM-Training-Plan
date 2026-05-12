#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 2e5+7;
vector<pair<int, bool>> p[N];//0 >> point to
int dp[N];

void dfs(int x, int fa){
    for(auto e: p[x]){
        int v = e.first;
        if(v == fa) continue;
        bool w = e.second;
        dp[1] += w;
        dfs(v, x);
    }
}

void dfs2(int x, int fa){
    for(auto e: p[x]){
        int v = e.first;
        if(v == fa) continue;
        bool w = e.second;
        if(w){//not point to
            dp[v] = dp[x] - 1;
        }
        else dp[v] = dp[x] + 1;
        dfs2(v, x);
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);   
    
    int n;
    cin >> n;
    foreach(1, n-1, i){
        int u, v;
        cin >> u >> v;
        p[u].push_back({v, 0});
        p[v].push_back({u, 1});
    }
    dfs(1, 0);
    dfs2(1, 0);
    int minN = dp[1];
    foreach(2, n, i){
        minN = min(minN, dp[i]);
    }
    cout << minN << '\n';
    foreach(1, n, i){
        if(minN == dp[i]) cout << i << ' ';
    }
}