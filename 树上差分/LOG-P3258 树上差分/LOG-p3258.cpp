#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 3e5+7, L = 20;
int num[N], st[N][25], dep[N], a[N];
vector<int> p[N];

void dfs(int x, int fa){
    dep[x] = dep[fa] + 1;
    st[x][0] = fa;
    foreach(1, L, j){
        st[x][j] = st[st[x][j-1]][j-1];
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
        if((t >> j) & 1) x = st[x][j];
    }
    if(x == y) return x;
    foreach_sub(L, 0, j){
        if(st[x][j] != st[y][j]){
            x = st[x][j], y = st[y][j];
        }
    }
    return st[x][0];
}

void dfs2(int x, int fa){
    for(auto v: p[x]){
        if(v == fa) continue;
        dfs2(v, x);
        num[x] += num[v];
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n;
    cin >> n;
    foreach(1, n, i){
        cin >> a[i];
    }
    foreach(1, n-1, i){
        int x, y;
        cin >> x >> y;
        p[x].push_back(y);
        p[y].push_back(x);
    }
    dfs(1, 0);
    foreach(2, n, i){
        int x = a[i-1], y = a[i];
        int lca = getLca(x, y);
        //cout << "LCA: " << lca << '\n';
        num[x]++, num[y]++;
        num[lca]--, num[st[lca][0]]--;
    }
    dfs2(1, 0);
    foreach(2, n, i) num[a[i]]--;
    foreach(1, n, i){
        cout << num[i] << '\n';
    }
}