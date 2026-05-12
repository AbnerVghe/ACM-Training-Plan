#include<bits/stdc++.h>
#define  ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 2e5+7;
ll flow[N], dp[N];
int sz[N];
//vector<pair<int, int>> p[N];
int head[N], to[N << 1], nxt[N << 1];
int degree[N];
ll weight[N << 1];
int cnt;

void addEdge(int u, int v, int w){
    nxt[++cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt;
}

void dfs(int x, int fa){
    //sz[x] = 1;
    flow[x] = 0;
    for(int e = head[x]; e; e = nxt[e]){
        int v = to[e];
        ll w = weight[e];
        if(v == fa) continue;
        dfs(v, x);
        flow[x] += (degree[v] == 1) ? w : min(w, flow[v]);
        //sz[x] += sz[v];
    }
}

void dfs2(int x, int fa){
    for(int e = head[x]; e; e = nxt[e]){
        int v = to[e];
        ll w = weight[e];
        if(v == fa) continue;
        if(degree[x] == 1){
            dp[v] = flow[v] + w;
        } 
        else{
            dp[v] = flow[v] + min(w, dp[x]-min(flow[v], w));
        }
        dfs2(v, x);
    }
}

void clear(int n){
    dp[1] = 0;
    cnt = 0;
    foreach(1, n, i){
        head[i] = degree[i] = 0;
    }
    foreach(1, 2*n, i){
        nxt[i] = to[i] = weight[i] = 0;
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        foreach(1, n-1, i){
            int x, y, z;
            cin >> x >> y >> z;
            addEdge(x, y, z);
            addEdge(y, x, z);
            degree[x]++, degree[y]++;
        }
        dfs(1, 0);
        dp[1] = flow[1];
        dfs2(1, 0);
        ll ans = dp[1];
        foreach(2, n, i){
            ans = max(ans, dp[i]);
        }
        cout << ans << '\n';
        clear(n);
    }
    
}