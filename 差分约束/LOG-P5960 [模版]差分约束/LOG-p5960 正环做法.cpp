#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 5e3+7;
int dis[N], cnt[N];
bool enter[N];
vector<pair<int, int>> p[N];
queue<int> q;
int n, m;

bool spfa(){
    dis[0] = 0;
    enter[0] = 1;
    q.push(0);
    while(q.size()){
        int u = q.front();
        q.pop();
        enter[u] = 0;
        for(auto e: p[u]){
            int v = e.first, w = e.second;
            if(dis[u] + w > dis[v]){
                dis[v] = dis[u] + w;
                if(enter[v]) continue;
                enter[v] = 1;
                q.push(v);
                cnt[v]++;
                if(cnt[v] > n) return 0;
            }
        }
    }
    return 1;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int m;
    cin >> n >> m;
    foreach(1, n, i){
        dis[i] = -INF;
        p[0].push_back({i, 0});
    }
    foreach(1, m, i){
        int x, y, z;//arr[x] - arr[y] <= z
        cin >> x >> y >> z;
        p[x].push_back({y, -z});
    }
    if(spfa()){
        foreach(1, n, i){
            cout << dis[i] << ' ';
        }
    }
    else cout << "NO";
}