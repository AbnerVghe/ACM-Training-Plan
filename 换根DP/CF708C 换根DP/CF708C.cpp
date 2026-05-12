#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 4e5+7;
int sz[N], maxSub[N], inner1[N], inner2[N], choose[N], outer[N];
int cnt;
int head[N], to[N << 1], nxt[N << 1];
int n;

void addEdge(int u, int v){
    nxt[++cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt;
}

void dfs1(int x, int fa){
    sz[x] = 1;
    for(int e = head[x]; e; e = nxt[e]){
        int v = to[e];
        if(v == fa) continue;
        dfs1(v, x);
        sz[x] += sz[v];
        if(sz[maxSub[x]] < sz[v]) maxSub[x] = v;
        int innerSz = (sz[v] <= n/2) ? sz[v] : inner1[v];
        if(inner1[x] < innerSz){
            choose[x] = v;
            inner2[x] = inner1[x];
            inner1[x] = innerSz;
        }
        else if(inner2[x] < innerSz){
            inner2[x] = innerSz;
        }
    }
}

void dfs2(int x, int fa){
    for(int e = head[x]; e; e = nxt[e]){
        int v = to[e];
        if(v == fa) continue;
        if(n - sz[v] <= n/2) outer[v] = n - sz[v];
        else if(v != choose[x]){
            outer[v] = max(outer[x], inner1[x]);
        }
        else{
            outer[v] = max(outer[x], inner2[x]);
        }
        dfs2(v, x);
    }
}

bool check(int x){
    if(sz[maxSub[x]] > n/2){
        return sz[maxSub[x]] - inner1[maxSub[x]] <= n/2;
    }
    if(n - sz[x] > n/2){
        return n - sz[x] - outer[x] <= n/2;
    }
    return 1;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    foreach(1, n-1, i){
        int u, v;
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    foreach(1, n, i) cout << check(i) << ' ';
}