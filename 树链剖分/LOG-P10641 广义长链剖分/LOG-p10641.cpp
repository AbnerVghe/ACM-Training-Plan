#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 2e5+7;
//len含义已经推广：最值钱长度（一块钱算一个长度
int arr[N], len[N], fa[N], son[N], top[N];
int indegree[N];
int money[N];
int cntD;
int ans[N];
vector<int> p[N];

void dfs1(int x, int f){
    fa[x] = f;
    for(auto v: p[x]){
        if(v == f) continue;
        dfs1(v, x);
        if(!son[x] || len[son[x]] < len[v]){
            son[x] = v;
        }
    }
    len[x] = len[son[x]] + arr[x];
}

void dfs2(int x, int t){
    top[x] = t;
    if(!son[x]) return;
    dfs2(son[x], t);
    for(auto v: p[x]){
        if(v == fa[x] || v == son[x]) continue;
        dfs2(v, v);
    }
}

bool cmp(int x, int y){
    return x > y;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n, k;
    cin >> n >> k;
    foreach(1, n, i){
        cin >> arr[i];
    }
    foreach(1, n-1, i){
        int u, v;
        cin >> u >> v;
        p[u].push_back(v);
        indegree[v]++;
    }
    int root = 0;
    foreach(1, n, i){
        if(!indegree[i]) root = i;
    }
    dfs1(root, 0);
    dfs2(root, root);
    foreach(1, n, i){
        if(top[i] == i){
            ans[++cntD] = len[i];
        }
    }
    //cout << cntD << '\n';
    sort(ans+1, ans+cntD+1, cmp);
    int res = 0;
    foreach(1, min(k, cntD), i){
        res += ans[i];
    }
    cout << res;
}
