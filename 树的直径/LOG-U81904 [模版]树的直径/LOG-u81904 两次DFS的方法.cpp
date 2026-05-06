#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

//本题边权可能为负，无法通过所有测试样例
const int N = 5e5+7;
int dist[N], last[N];//距离和父亲是谁(用于追踪路径)
vector<pair<int, int>> p[N];
int START, END;

void dfs(int x, int fa, int w){
    last[x] = fa;
    dist[x] = dist[fa] + w;
    for(auto e: p[x]){
        int v = e.first, w = e.second;
        if(v == fa) continue;
        dfs(v, x, w);
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
    dist[1] = 0;
    dfs(1, 0, 0);
    START = 1;
    foreach(2, n, i){
        if(dist[i] > dist[START]){
            START = i;
        }
    }
    dist[START] = 0;
    dfs(START, 0, 0);
    END = 1;
    foreach(2, n, i){
        if(dist[i] > dist[END]){
            END = i;
        }
    }
    cout << dist[END];
}