#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 2e5+7;
int dist[N], last[N];
int diameter;
bool isOnDia[N];
vector<pair<int, int>> p[N];

void dfs(int x, int fa, int w){
    last[x] = fa;
    dist[x] = dist[fa] + w;
    for(auto e: p[x]){
        int v = e.first, w = e.second;
        if(v == fa) continue;
        dfs(v, x, w);
    }
}

int maxDist(int x, int fa, int c){
    int ans = c;
    for(auto e: p[x]){
        int v = e.first, w = e.second;
        if(v == fa || isOnDia[v]) continue;
        ans = max(ans, maxDist(v, x, c+w));
    }
    return ans;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n;
    cin >> n;
    foreach(1, n-1, i){
        int a, b, c;
        cin >> a >> b >> c;
        p[a].push_back({b, c});
        p[b].push_back({a, c});
    }
    dfs(1, 0, 0);
    int START = 1;
    foreach(2, n, i){
        if(dist[i] > dist[START]) START = i;
    }
    dist[START] = 0;
    dfs(START, 0, 0);
    int END = 1;
    foreach(2, n, i){
        if(dist[i] > dist[END]) END = i;
    }
    diameter = dist[END];
    for(int x = END; x; x = last[x]){
        isOnDia[x] = 1;
    }
    int L = START, R = END;
    for(int x = last[END]; x != START; x = last[x]){
        int tmp = maxDist(x, 0, 0);
        if(tmp == diameter - dist[x]) R = x;
        if(tmp == dist[x] && L == START) L = x;
    }
    int ans = 0;
    if(L == R) ans = 0;
    else{
        ans = 1;
        for(int x = last[R]; x != L; x = last[x]){
            ans++;
        }
    }
    cout << diameter << '\n' << ans;
}