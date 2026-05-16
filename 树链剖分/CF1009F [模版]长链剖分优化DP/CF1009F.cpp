#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 1e6+7;
int len[N], dfn[N], son[N], cnt;
int ansx[N];
int dp[N];
vector<int> p[N];

void setDp(int x, int i, int v){
    dp[dfn[x]+i] = v;
}

int getDp(int x, int i){
    return dp[dfn[x]+i];
}

void dfs1(int x, int fa){
    for(auto v: p[x]){
        if(v == fa) continue;
        dfs1(v, x);
        if(!son[x] || len[son[x]] < len[v]){
            son[x] = v;
        }
    }
    len[x] = len[son[x]] + 1;
}

void dfs2(int x, int fa){
    dfn[x] = ++cnt;
    setDp(x, 0, 1);
    ansx[x] = 0;
    if(!son[x]) return;
    dfs2(son[x], x);
    for(auto v: p[x]){
        if(v == fa || v == son[x]) continue;
        dfs2(v, x);
    }
    ansx[x] = ansx[son[x]] + 1;
    for(auto v: p[x]){
        if(v == fa || v == son[x]) continue;
        foreach(1, len[v], i){
            setDp(x, i, getDp(x, i)+getDp(v, i-1));
            if(getDp(x, i) > getDp(x, ansx[x]) || (getDp(x, i) == getDp(x, ansx[x]) && i < ansx[x])){
                ansx[x] = i;
            }
        }
    }
    if(getDp(x, ansx[x]) == 1) ansx[x] = 0;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n;
    cin >> n;
    foreach(1, n-1, i){
        int x, y;
        cin >> x >> y;
        p[x].push_back(y);
        p[y].push_back(x);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    foreach(1, n, i){
        cout << ansx[i] << '\n';
    }
}