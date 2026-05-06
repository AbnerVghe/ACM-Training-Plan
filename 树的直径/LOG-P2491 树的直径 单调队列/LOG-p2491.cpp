#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 3e5+7;
vector<pair<int, int>> p[N];
int dist[N], last[N], maxDist[N], pred[N];
int dia;
bool isOnDia[N];
int que[N];

void dfs(int x, int fa, int w){
    last[x] = fa;
    dist[x] = dist[fa] + w;
    pred[x] = w;
    for(auto e: p[x]){
        int v = e.first, w = e.second;
        if(v == fa) continue;
        dfs(v, x, w);
    }
}

int getMaxDist(int x, int fa, int c){
    int ans = c;
    for(auto e: p[x]){
        int v = e.first, w = e.second;
        if(v == fa || isOnDia[v]) continue;
        ans = max(ans, getMaxDist(v, x, c+w));
    }
    return ans;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n, s;
    cin >> n >> s;
    foreach(1, n-1, i){
        int u, v, w;
        cin >> u >> v >> w;
        p[u].push_back({v, w});
        p[v].push_back({u, w});
    }
    int START = 1, END = 1;
    dfs(1, 0, 0);
    foreach(2, n, i){
        if(dist[i] > dist[START]) START = i;
    }
    dist[START] = 0;
    dfs(START, 0, 0);
    foreach(2, n, i){
        if(dist[i] > dist[END]) END = i;
    }
    dia = dist[END];
    for(int x = END; x; x = last[x]){
        isOnDia[x] = 1;
    }
    for(int x = last[END]; x != START; x = last[x]){
        maxDist[x] = getMaxDist(x, 0, 0);
    }
    int suml = 0, sumr = 0;
    int h = 0, t = 0;
    int ans = LONG_LONG_MAX;
    for(int l = END, r = END; l; l = last[l]){
        while(r && sumr-suml+pred[r] <= s){
            while(h < t && maxDist[que[t-1]] <= maxDist[r]) t--;
            sumr += pred[r];
            que[t++] = r;
            r = last[r];
        }
        ans = min(ans, max(max(suml, dia-sumr), maxDist[que[h]]));
        if(que[h] == l) h++;
        suml += pred[l];
    }
    cout << ans;
}