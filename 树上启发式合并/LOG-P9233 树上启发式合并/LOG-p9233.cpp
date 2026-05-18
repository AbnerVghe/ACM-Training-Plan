#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 2e5+7;
int arr[N];
int sz[N], son[N];
int colorCnt[N], colorNum[N];
vector<int> p[N];
int ans;

void dfs1(int x){
    sz[x] = 1;
    for(auto v: p[x]){
        dfs1(v);
        sz[x] += sz[v];
        if(!son[x] || sz[son[x]] < sz[v]){
            son[x] = v;
        }
    }
}

void effect(int x){
    int cnt = ++colorCnt[arr[x]];
    colorNum[cnt-1]--;
    colorNum[cnt]++;
    for(auto v: p[x]){
        effect(v);
    }
}

void cancel(int x){
    int cnt = --colorCnt[arr[x]];
    colorNum[cnt+1]--;
    colorNum[cnt]++;
    for(auto v: p[x]){
        cancel(v);
    }
}

void dfs2(int x, bool keep){
    for(auto v: p[x]){
        if(v == son[x]) continue;
        dfs2(v, 0);
    }
    if(son[x]){
        dfs2(son[x], 1);
    }
    int cnt = ++colorCnt[arr[x]];
    colorNum[cnt-1]--;
    colorNum[cnt]++;
    for(auto v: p[x]){
        if(v == son[x]) continue;
        effect(v);
    }
    if(colorCnt[arr[x]] * colorNum[colorCnt[arr[x]]] == sz[x]){
        ans++;
    }
    if(!keep) cancel(x);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n;
    cin >> n;
    foreach(1, n, i){
        int c, f;
        cin >> c >> f;
        arr[i] = c;
        if(f) p[f].push_back(i);
    }
    dfs1(1);
    dfs2(1, 0);
    cout << ans;
}