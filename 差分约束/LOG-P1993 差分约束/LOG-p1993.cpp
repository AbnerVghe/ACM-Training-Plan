#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 5e3+7;
int dis[N], cnt[N];
bool enter[N];
queue<int> q;
vector<pair<int, int>> p[N];
int n; 

bool spfa(){
    dis[0] = 0;
    enter[0] = 1;
    q.push(0);
    while(q.size()){
        int u = q.front();
        enter[u] = 0;
        q.pop();
        for(auto e: p[u]){
            int v = e.first, w = e.second;
            if(dis[v] > dis[u] + w){
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
        dis[i] = INF;
        p[0].push_back({i, 0});
    }
    foreach(1, m, i){
        int opt, a, b, c;
        cin >> opt >> a >> b;
        if(opt == 1){
            cin >> c;
            p[a].push_back({b, -c});
        }
        else if(opt == 2){
            cin >> c;
            p[b].push_back({a, c});
        }
        else{
            p[b].push_back({a, 0});
            p[a].push_back({b, 0});
        }
    }
    if(spfa()){
        cout << "Yes";
    }
    else cout << "No";
}