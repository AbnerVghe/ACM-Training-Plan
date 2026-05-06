#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 5e5+7;
int dist[N];//从u开始必须往下走能走出的最大距离
int ans[N];//路径必须包含u且以u为最高点能得到的最大路径长度
vector<pair<int, int>> p[N];

void dfs(int x, int fa){
    for(auto e: p[x]){
        int v = e.first, w = e.second;
        if(v == fa) continue;
        dfs(v, x);
        ans[x] = max(ans[x], dist[x]+dist[v]+w);
        dist[x] = max(dist[x], dist[v]+w);
    }
}  

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n;
    cin >> n;
    foreach(1, n-1, i){
        int u, v, w;
        cin >> u >> v >> w;
        p[u].push_back({v, w});
        p[v].push_back({u, w});
    }
    dfs(1, 0);
    int ANS = INT_MIN;
    foreach(1, n, i){
        ANS = max(ANS, ans[i]);
    }   
    cout << ANS;
}