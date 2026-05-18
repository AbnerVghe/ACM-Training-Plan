#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 1e5+7;
int fa[N], sz[N], son[N];
vector<int> p[N];
int ans[N];
int arr[N];
int cntColor[N], diffColor;

void dfs1(int x, int f){//重链剖分
    fa[x] = f;
    sz[x] = 1;
    for(auto v: p[x]){
        if(v == f) continue;
        dfs1(v, x);
        sz[x] += sz[v];
        if(!son[x] || sz[son[x]] < sz[v]){
            son[x] = v;
        }
    }
}

void effect(int x){//以x为节点的子树进行一次贡献
    if(++cntColor[arr[x]] == 1){
        diffColor++;
    }
    for(auto v: p[x]){
        if(v == fa[x]) continue;
        effect(v);
    }
}

void cancel(int x){//取消贡献
    if(--cntColor[arr[x]] == 0){
        diffColor--;
    }
    for(auto v: p[x]){
        if(v == fa[x]) continue;
        cancel(v);
    }
}

void dfs2(int x, bool keep){//树上启发式合并
    for(auto v: p[x]){//遍历轻儿子，不保留信息
        if(v == fa[x] || v == son[x]) continue;
        dfs2(v, 0);
    }
    if(son[x]){//遍历重儿子，保留信息
        dfs2(son[x], 1);
    }
    if(++cntColor[arr[x]] == 1) diffColor++;//自己节点贡献一次
    for(auto v: p[x]){//重新遍历轻儿子
        if(v == fa[x] || v == son[x]) continue;
        effect(v);
    }
    ans[x] = diffColor;
    if(!keep) cancel(x);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n;
    cin >> n;
    foreach(1, n-1, i){
        int u, v;
        cin >> u >> v;
        p[u].push_back(v);
        p[v].push_back(u);
    }
    foreach(1, n, i){
        cin >> arr[i];
    }
    dfs1(1, 0);
    dfs2(1, 0);
    int m;
    cin >> m;
    while(m--){
        int q;
        cin >> q;
        cout << ans[q] << '\n';
    }
}