#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 1e5+7;
int center;
int sz[N];
vector<pair<int, int>> p[N];
int cow[N], path[N];
int n;
int allN;

void dfs(int x, int fa){
    sz[x] = cow[x];
    int maxSub = 0;
    for(auto e: p[x]){
        int v = e.first;
        if(v == fa) continue;
        dfs(v, x);
        sz[x] += sz[v];
        maxSub = max(maxSub, sz[v]);
    }
    maxSub = max(maxSub, allN-sz[x]);
    if(maxSub <= allN/2) center = x;
}

void dfs2(int x, int fa){
    for(auto e: p[x]){
        int v = e.first, w = e.second;
        if(v == fa) continue;
        path[v] = path[x] + w;
        dfs2(v, x);
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    foreach(1, n, i){
        int tmp;
        cin >> tmp;
        cow[i] = tmp;
        allN += tmp;
    }
    foreach(1, n-1, i){
        int a, b, l;
        cin >> a >> b >> l;
        p[a].push_back({b, l});
        p[b].push_back({a, l});
    }
    dfs(1, 0);
    path[center] = 0;
    dfs2(center, 0);
    int ans = 0;
    foreach(1, n, i){
        ans += path[i] * cow[i];
    }
    cout << ans;
}