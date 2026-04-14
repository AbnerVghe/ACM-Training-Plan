#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

const int N = 1e4+7;
vector<int> p[N];
int ans = 0;

int dfs(int x, int fa){//0:不放无信号,1:不放有信号,2:放了有信号
    int sz = 0, cnt0 = 0, cnt1 = 0, cnt2 = 0;
    for(auto v: p[x]){
        if(v == fa) continue;

        int son = dfs(v, x);
        if(son == 0) cnt0++;
        else if(son == 1) cnt1++;
        else cnt2++;
        sz++;
    }
    
    if(!sz) return 0;
    if(cnt0){
        ans++;
        return 2;
    }
    if(cnt2) return 1;
    return 0;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    foreach(1, n-1, i){
        int u, v;
        cin >> u >> v;
        p[u].push_back(v);
        p[v].push_back(u);
    }
    int put = (dfs(1, 0) == 0) ? 1 : 0;
    cout << ans + put;
}