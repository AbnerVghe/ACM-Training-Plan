#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 1e5+7;
vector<int> p[N];
bool isOnDia[N];
int dist[N], last[N];
int dia1, dia2;

void dfs(int x, int fa){
    last[x] = fa;
    if(fa) dist[x] = dist[fa] + 1;
    for(auto v: p[x]){
        if(v == fa) continue;
        dfs(v, x);
    }
}

void dp(int x, int fa){
    for(auto v: p[x]){
        if(v == fa) continue;
        dp(v, x);
        int w = (isOnDia[x] && isOnDia[v]) ? -1 : 1;
        dia2 = max(dia2, dist[x]+dist[v]+w);
        dist[x] = max(dist[x], dist[v]+w);
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n, k;
    cin >> n >> k;
    foreach(1, n-1, i){
        int a, b;
        cin >> a >> b;
        p[a].push_back(b);
        p[b].push_back(a);
    }
    dfs(1, 0);
    int START = 1;
    foreach(2, n, i){
        if(dist[i] > dist[START]) START = i;
    }
    dist[START] = 0;
    dfs(START, 0);
    int END = 1;
    foreach(2, n, i){
        if(dist[i] > dist[END]) END = i;
    }
    if(k == 1){
        cout << 2*(n-1) - dist[END] + 1<< '\n';
    }
    else{
        dia1 = dist[END];
        for(int x = END; x; x = last[x]){
            isOnDia[x] = 1;
        }
        foreach(1, n, i) dist[i] = 0;
        dp(1, 0);
        cout << 2*(n-1) - dia1 - dia2 + 2 << '\n';
    }

}