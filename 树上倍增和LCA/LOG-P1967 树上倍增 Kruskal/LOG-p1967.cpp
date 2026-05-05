#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 1e4+7, M = 5e4+7, L = 20;
vector<pair<int, int>> p[N];
bool vis[N];
int fa[N];
int st[N][25], stMin[N][25], dep[N];

void init(int n){
    foreach(1, n, i) fa[i] = i;
}

int find(int x){
    if(fa[x] != x){
        fa[x] = find(fa[x]);
    }
    return fa[x];
}

bool add(int x, int y){
    int fx = find(x), fy = find(y);
    if(fx != fy){
        fa[fx] = fy;
        return 1;
    }
    return 0;
}

struct Node{
    int x, y, w;
}edge[M];

bool cmp(Node &A, Node &B){
    return A.w > B.w;
}

void dfs(int x, int fa, int w){
    vis[x] = 1;
    if(!fa){
        st[x][0] = x;
        stMin[x][0] = INF;
        dep[x] = 1;
    }
    else{
        st[x][0] = fa;
        stMin[x][0] = w;
        dep[x] = dep[fa] + 1;
    }

    foreach(1, L, j){
        st[x][j] = st[st[x][j-1]][j-1];
        stMin[x][j] = min(stMin[st[x][j-1]][j-1], stMin[x][j-1]);
    }
    for(auto e: p[x]){
        int v = e.first, w = e.second;
        if(v == fa) continue;
        dfs(v, x, w);
    }  
}


signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n, m;
    cin >> n >> m;
    foreach(1, m, i){
        int x, y, z;
        cin >> x >> y >> z;
        edge[i] = {x, y, z};
    }
    sort(edge+1, edge+m+1, cmp);
    init(n);
    foreach(1, m, i){
        int x = edge[i].x, y = edge[i].y, w = edge[i].w;
        if(!add(x, y)) continue;
        p[x].push_back({y, w});
        p[y].push_back({x, w});
    }
    foreach(1, n, i){
        if(!vis[i]) dfs(i, 0, INF);
    }
    int q;
    cin >> q;
    foreach(1, q, i){
        int x, y;
        cin >> x >> y;
        if(find(x) != find(y)){
            cout << -1 << '\n';
        }
        else{
            if(dep[x] < dep[y]) swap(x, y);
            int t = dep[x] - dep[y], ans = INF;
            foreach_sub(L, 0, j){
                if((t>>j)&1){
                    ans = min(ans, stMin[x][j]);
                    x = st[x][j];
                }
            }
            if(x != y){
                foreach_sub(L, 0, j){
                    if(st[x][j] != st[y][j]){
                        ans = min(ans, min(stMin[x][j], stMin[y][j]));
                        x = st[x][j], y = st[y][j];
                    }
                }
                ans = min(ans, min(stMin[x][0], stMin[y][0]));
            }
            cout << ans << '\n';
        }
    }
}