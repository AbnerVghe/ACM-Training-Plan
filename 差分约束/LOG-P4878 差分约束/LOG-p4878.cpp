#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 1010;
int dis[N], cnt[N];
bool enter[N];
vector<pair<int, int>> p[N];
queue<int> q;
int n;

bool spfa(int s){
    foreach(0, n, i){
        dis[i] = INF;
        enter[i] = cnt[i] = 0;
    }
    while(q.size()) q.pop();

    dis[s] = 0;
    enter[s] = 1;
    q.push(s);
    while(q.size()){
        int u = q.front();
        enter[u] = 0;
        q.pop();
        for(auto e: p[u]){
            int v = e.first, w = e.second;
            if(dis[u] + w < dis[v]){
                dis[v] = dis[u] + w;
                if(enter[v]) continue;
                enter[v] = 1;
                cnt[v]++;
                q.push(v);
                if(cnt[v] > n) return 0;
            }
        }
    }
    return 1;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int m1, m2;
    cin >> n >> m1 >> m2;
    foreach(1, n, i){
        p[0].push_back({i, 0});
    }
    foreach(1, n-1, i){
        p[i+1].push_back({i, 0});
    }
    foreach(1, m1, i){
        int a, b, d;
        cin >> a >> b >> d;
        p[a].push_back({b, d});
    }
    foreach(1, m2, i){
        int a, b, d;
        cin >> a >> b >> d;
        p[b].push_back({a, -d});
    }
    if(!spfa(0)){
        cout << -1;
    }
    else{
        spfa(1);
        if(dis[n] == INF) cout << -2;
        else{
            cout << dis[n];
        }
    }
}