#include<bits/stdc++.h>
#define ull unsigned long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 1e5+7, L = 20, base = 499;
vector<int> p[N];
int a[N];
int dep[N];
int st[N][25];
ull kpow[N];
ull stup[N][25], stdown[N][25];

void dfs(int x, int fa){
    if(!fa){
        st[x][0] = 0;
        dep[x] = 1;
        stup[x][0] = stdown[x][0] = 0;
    }
    else{
        st[x][0] = fa;
        dep[x] = dep[fa] + 1;
        stup[x][0] = stdown[x][0] = a[fa];
    }

    foreach(1, L, i){
        int v = st[x][i-1];
        st[x][i] = st[v][i-1];
        stup[x][i] = stup[x][i-1] * kpow[1 << (i-1)] + stup[v][i-1];
        stdown[x][i] = stdown[v][i-1] * kpow[1 << (i-1)] + stdown[x][i-1];
    }
    for(auto v: p[x]){
        if(v == fa) continue;
        dfs(v, x);
    }
}

int getLca(int x, int y){
    if(dep[x] < dep[y]) swap(x, y);
    int t = dep[x] - dep[y];
    foreach_sub(L, 0, j){
        if((t>>j)&1){
            x = st[x][j];
        }
    }
    if(x == y) return x;
    foreach_sub(L, 0, j){
        if(st[x][j] != st[y][j]){
            x = st[x][j], y = st[y][j];
        }
    }
    return st[x][0];
}

ull Hash(int from, int lca, int to){
    ull up = a[from];
    foreach_sub(L, 0, i){
        if(dep[st[from][i]] >= dep[lca]){
            up = up * kpow[1 << i] + stup[from][i];
            from = st[from][i];
        }
    }
    if(to == lca) return up;
    ull down = a[to];
    int height = 1;
    foreach_sub(L, 0, i){
        if(dep[st[to][i]] > dep[lca]){
            down = stdown[to][i] * kpow[height] + down;
            height += 1 << i;
            to = st[to][i];
        }
    }
    return up * kpow[height] + down;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n;
    cin >> n;
    kpow[0] = 1;
    foreach(1, n, i){
        kpow[i] = kpow[i-1] * base;
    }
    string s;
    cin >> s;
    foreach(1, n, i){
        a[i] = s[i-1]-'a'+1;
    }
    foreach(1, n, i){
        int v;
        cin >> v;
        if(!v) continue;
        p[v].push_back(i);
        p[i].push_back(v);
    }
    dfs(1, 0);
    int q;
    cin >> q;
    while(q--){
        int u, v;
        cin >> u >> v;
        int lca = getLca(u, v);
        ull hash1 = Hash(u, lca, v), hash2 = Hash(v, lca, u);
        cout << ((hash1 == hash2) ? "YES" : "NO") << '\n';
    }
}