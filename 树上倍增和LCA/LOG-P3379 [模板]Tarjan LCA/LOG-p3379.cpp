#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 5e5+7;
vector<int> p[N];
bool vis[N];
vector<pair<int, int>> qss[N];
int ans[N];
int fa[N];
int n;

void init(){
    foreach(1, n, i){
        fa[i] = i;
    }
}

int find(int x){
    if(x != fa[x]){
        fa[x] = find(fa[x]);
    }
    return fa[x];
}

void add(int x, int y){//add y to x
    int fx = find(x), fy = find(y);
    if(fx != fy){
        fa[fy] = fx;
    }
}

void dfs(int x, int fa){
    vis[x] = 1;
    for(auto v: p[x]){
        if(v == fa) continue;
        dfs(v, x);
        add(x, v);
    }
    for(auto qs: qss[x]){
        int v = qs.first, id = qs.second;
        if(v == x) ans[id] = x;
        else{
            if(!vis[v]) continue;
            
            ans[id] = find(v);
        }
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int m, root;
    cin >> n >> m >> root;
    init();
    foreach(1, n, i) vis[i] = 0;
    foreach(1, n-1, i){
        int x, y;
        cin >> x >> y;
        p[x].push_back(y);
        p[y].push_back(x);
    }
    foreach(1, m, i){
        int a, b;
        cin >> a >> b;
        qss[a].push_back({b, i});
        qss[b].push_back({a, i});
    }
    dfs(root, 0);
    foreach(1, m, i) cout << ans[i] << '\n';
}