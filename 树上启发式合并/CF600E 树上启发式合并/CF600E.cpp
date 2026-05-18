#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 1e5+7;
int arr[N];
vector<int> p[N];
int fa[N], son[N], sz[N];
int colorCnt[N], maxCnt[N], ans[N];

void dfs1(int x, int f){
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

void effect(int x, int h){
    int cnt = ++colorCnt[arr[x]];
    if(cnt == maxCnt[h]){
        ans[h] += arr[x];
    }
    else if(cnt > maxCnt[h]){
        maxCnt[h] = cnt;
        ans[h] = arr[x];
    }
    for(auto v: p[x]){
        if(v == fa[x]) continue;
        effect(v, h);
    }
}

void cancel(int x){
    colorCnt[arr[x]] = 0;
    maxCnt[x] = 0;
    for(auto v: p[x]){
        if(v == fa[x]) continue;
        cancel(v);
    }
}

void dfs2(int x, bool keep){
    for(auto v: p[x]){
        if(v == fa[x] || v == son[x]) continue;
        dfs2(v, 0);
    }
    if(son[x]){
        dfs2(son[x], 1);
    }
    int cnt = ++colorCnt[arr[x]];
    maxCnt[x] = maxCnt[son[x]];
    ans[x] = ans[son[x]];
    if(cnt == maxCnt[x]){
        ans[x] += arr[x];
    }
    else if(cnt > maxCnt[x]){
        maxCnt[x] = cnt;
        ans[x] = arr[x];
    }
    for(auto v: p[x]){
        if(v == fa[x] || v == son[x]) continue;
        effect(v, x);
    }
    if(!keep) cancel(x);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n;
    cin >> n;
    foreach(1, n, i){
        cin >> arr[i];
    }
    foreach(1, n-1, i){
        int x, y;
        cin >> x >> y;
        p[x].push_back(y);
        p[y].push_back(x);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    foreach(1, n, i){
        cout << ans[i] << ' ';
    }
}