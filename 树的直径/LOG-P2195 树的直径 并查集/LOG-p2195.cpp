#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 3e5+7;
int fa[N], dia[N], dist[N];
vector<int> p[N];
int n;

void build(){
    foreach(1, n, i){
        fa[i] = i;
    }
}

int find(int x){
    if(x != fa[x]){
        fa[x] = find(fa[x]);
    }
    return fa[x];
}

void dp(int x, int f){
    for(auto v: p[x]){
        if(v == f) continue;
        dp(v, x);
        dia[x] = max(dia[x], max(dia[v], dist[x]+dist[v]+1));
        dist[x] = max(dist[x], dist[v]+1);
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int m, q;
    cin >> n >> m >> q;
    build();
    while(m--){
        int x, y;
        cin >> x >> y;
        p[x].push_back(y);
        p[y].push_back(x);
        x = find(x), y = find(y);
        fa[x] = y;   
    }
    foreach(1, n, i){
        if(fa[i] == i){
            dp(i, 0);
        }
    }
    while(q--){
        int opt, x, y;
        cin >> opt;
        if(opt == 1){
            cin >> x;
            x = find(x);
            cout << dia[x] << '\n';
        }
        else{
            cin >> x >> y;
            x = find(x), y = find(y);
            if(x != y){
                fa[x] = y;
                dia[y] = max(max(dia[x], dia[y]), (dia[x]+1)/2+(dia[y]+1)/2+1);
            }
        }
    }
}