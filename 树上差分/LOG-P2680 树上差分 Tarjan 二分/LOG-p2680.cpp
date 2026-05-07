#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 3e5+7, M = 3e6+7;
int lca[N], fa[N], num[N];
//vector<pair<int, int>> p[N];
vector<pair<int, int>> qss[M];
pair<int, int> plan[M];
int cnt, head[N], nxt[M], to[M], wgh[M];
bool vis[N];
int dist[N], cost[M], maxCost;
int n, m;
int atLeast, beyond;

void build(){
    foreach(1, n, i){
        fa[i] = i;
    }
}

void addEdge(int u, int v, int w){
    nxt[++cnt] = head[u];
    to[cnt] = v;
    wgh[cnt] = w;
    head[u] = cnt;
}

int find(int x){
    if(fa[x] != x){
        fa[x] = find(fa[x]);
    }
    return fa[x];
}

void add(int x, int y){//add fx to fy
    int fx = find(x), fy = find(y);
    if(fx != fy){
        fa[fx] = fy;
    }
}

void tarjan(int x, int f, int w){
    vis[x] = 1;
    dist[x] = dist[f] + w;
    for(int e = head[x]; e; e = nxt[e]){
        int v = to[e], w = wgh[e];
        if(v == f) continue;
        tarjan(v, x, w);
        add(v, x);
    }
    for(auto qs: qss[x]){
        int v = qs.first, id = qs.second;
        if(!vis[v]) continue;
        lca[id] = find(v);
        cost[id] = dist[x] + dist[v] - 2*dist[lca[id]];
        maxCost = max(maxCost, cost[id]);
    }
    //fa[x] = f;
}

bool dfs(int, int, int);

bool check(int limit){
    atLeast = maxCost - limit;
    foreach(0, n, i) num[i] = 0;
    beyond = 0;
    foreach(1, m, i){
        if(cost[i] > limit){
            num[plan[i].first]++, num[plan[i].second]++;
            num[lca[i]] -= 2;
            beyond++;
        }
    }
    return beyond == 0 || dfs(1, 0, 0);
}

bool dfs(int x, int f, int w){
    for(int e = head[x]; e; e = nxt[e]){
        int v = to[e], weight = wgh[e];
        if(v == f) continue;
        if(dfs(v, x, weight)) return 1;
    }
    for(int e = head[x]; e; e = nxt[e]){
        int v = to[e];
        if(v == f) continue;
        num[x] += num[v];
    }
    return num[x] == beyond && w >= atLeast;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    foreach(1, n-1, i){
        int a, b, t;
        cin >> a >> b >> t;
        addEdge(a, b, t);
        addEdge(b, a, t);
    }
    build();
    foreach(1, m, i){
        int u, v;
        cin >> u >> v;
        plan[i] = {u, v};
        qss[u].push_back({v, i});
        qss[v].push_back({u, i});
    }
    tarjan(1, 0, 0);
    int L = 0, R = maxCost;
    int ans = 0;
    while(L <= R){
        int mid = (L + R) >> 1;
        if(check(mid)){
            ans = mid;
            R = mid-1;
        }
        else L = mid+1;
    }
    cout << ans;
}