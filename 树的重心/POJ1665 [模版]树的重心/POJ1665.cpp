#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 2e4+7;
int sz[N];
vector<int> p[N];
int n;
int center, minSub;

void clear(){
    foreach(1, n, i) p[i].clear();
}

void dfs(int x, int fa){
    sz[x] = 1;
    int maxSub = 0;//以x为根时，最大子树的大小
    for(auto v: p[x]){
        if(v == fa) continue;
        dfs(v, x);
        sz[x] += sz[v];
        maxSub = max(maxSub, sz[v]);
    }
    maxSub = max(maxSub, n-sz[x]);
    if(maxSub < minSub || (maxSub == minSub && x < center)){
        minSub = maxSub;
        center = x;
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int T;
    cin >> T;
    while(T--){
        center = 0;
        minSub = INT_MAX;
        cin >> n;
        foreach(1, n-1, i){
            int u, v;
            cin >> u >> v;
            p[u].push_back(v);
            p[v].push_back(u);
        }
        dfs(1, 0);
        cout << center << ' ' << minSub << '\n';

        clear();
    }
}