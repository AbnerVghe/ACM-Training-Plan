#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

struct Edge{
    int v, w;
};

const int N = 5e5+7, L = 21;
int dep[N], sz[N], son[N], eor[N];
vector<Edge> p[N]; 
int maxDep[1 << 23], ans[N];

void dfs1(int x, int f, int s){
    dep[x] = dep[f] + 1;
    sz[x] = 1;
    eor[x] = s;
    for(auto e: p[x]){
        int v = e.v, w = e.w;
        if(v == f) continue;
        dfs1(v, x, s ^ (1 << w));
        sz[x] += sz[v];
        if(!son[x] || sz[son[x]] < sz[v]){
            son[x] = v;
        }
    }
}

void effect(int x){
    maxDep[eor[x]] = max(maxDep[eor[x]], dep[x]);
    for(auto e: p[x]){
        int v = e.v;
        effect(v);
    }
}

void cancel(int x){
    maxDep[eor[x]] = 0;
    for(auto e: p[x]){
        int v = e.v;
        cancel(v);
    }
}

void getAns(int light, int x){
    if(maxDep[eor[light]]){
        ans[x] = max(ans[x], maxDep[eor[light]]+dep[light]-2*dep[x]);
    }
    foreach(0, L, i){
        int s = eor[light] ^ (1 << i);
        if(maxDep[s]){
            ans[x] = max(ans[x], maxDep[s]+dep[light]-2*dep[x]);
        }
    }
    for(auto e: p[light]){
        int v = e.v;
        getAns(v, x);
    }
}

void dfs2(int x, bool keep){
    for(auto e: p[x]){
        int v = e.v;
        if(v == son[x]) continue;
        dfs2(v, 0);
    }
    if(son[x]){
        dfs2(son[x], 1);
    }

    for(auto e: p[x]){
        int v = e.v;
        ans[x] = max(ans[x], ans[v]);
    }

    if(maxDep[eor[x]]){//0000
        ans[x] = max(ans[x], maxDep[eor[x]] - dep[x]);
    }
    foreach(0, L, i){
        int s = eor[x] ^ (1 << i);
        if(maxDep[s]){
            ans[x] = max(ans[x], maxDep[s]-dep[x]);
        }
    }

    maxDep[eor[x]] = max(maxDep[eor[x]], dep[x]);

    for(auto e: p[x]){
        int v = e.v;
        if(v == son[x]) continue;
        getAns(v, x);
        effect(v);
    }

    if(!keep) cancel(x);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n;
    cin >> n;
    foreach(2, n, i){
        int f;
        char w;
        cin >> f >> w;
        p[f].push_back({i, w-'a'});
    }
    dfs1(1, 0, 0);
    dfs2(1, 0);
    foreach(1, n, i){
        cout << ans[i] << ' ';
    }
}