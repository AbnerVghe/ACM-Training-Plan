#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

const int N = 6e3+7;
int r[N];
vector<int> p[N];

pair<int, int> dfs(int x){//include root and exclude root
    int sum1 = 0, sum0 = 0;
    for(auto v: p[x]){
        pair<int, int> info = dfs(v);
        sum1 += info.first;
        sum0 += info.second;
    }
    int ans1 = sum0+r[x], ans0 = max(sum0, sum1);
    return {ans1, ans0};
}

int du[N];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    foreach(1, n, i) cin >> r[i];
    foreach(1, n-1, i){
        int u, v;
        cin >> v >> u;
        p[u].push_back(v);
        du[v]++;
    }
    int root = 0;
    foreach(1, n, i){
        if(!du[i]) root = i;
    }
    pair<int, int> ans = dfs(root);
    cout << max(ans.first, ans.second);
}