#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 5e4+7;
int sz[N], mxSub[N];
vector<int> p[N];
int n;

void dfs(int x, int fa){
    sz[x] = 1;
    int maxSub = 0;
    for(auto v: p[x]){
        if(v == fa) continue;
        dfs(v, x);
        sz[x] += sz[v];
        maxSub = max(maxSub, sz[v]);
    }
    maxSub = max(maxSub, n-sz[x]);
    mxSub[x] = maxSub;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    foreach(1, n-1, i){
        int a, b;
        cin >> a >> b;
        p[a].push_back(b);
        p[b].push_back(a);
    }
    dfs(1, 0);
    foreach(1, n, i){
        if(mxSub[i] <= n/2){
            cout << i << ' ';
        }
    }
}