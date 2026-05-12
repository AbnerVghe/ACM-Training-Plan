#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 5e5+7;
int inner1[N], inner2[N], incost[N], outer[N], outcost[N], choose[N], people[N];
int cnt, head[N], to[N << 1], weight[N << 1], nxt[N << 1];
int n, k;

void addEdge(int u, int v, int w){
    nxt[++cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt;
}

void dfs(int x, int fa){
    for(int e = head[x]; e; e = nxt[e]){
        int v = to[e], w = weight[e];
        if(v == fa) continue;
        dfs(v, x);
        people[x] += people[v];
        if(!people[v]) continue;
        incost[x] += incost[v] + 2*w; 
        int inner = inner1[v] + w;
        if(inner1[x] < inner){
            choose[x] = v;
            inner2[x] = inner1[x];
            inner1[x] = inner;
        }
        else if(inner2[x] < inner){
            inner2[x] = inner;
        }
    }
}

void dfs2(int x, int fa){
    for(int e = head[x]; e; e = nxt[e]){
        int v = to[e], w = weight[e];
        if(v == fa) continue;
        if(k - people[v] > 0){
           if(!people[v]){
                outcost[v] = outcost[x] + incost[x] + 2*w; 
            }
            else{
                outcost[v] = outcost[x] + incost[x] - incost[v];
            } 
            if(choose[x] != v){
                outer[v] = max(outer[x], inner1[x]) + w;
            }
            else{
                outer[v] = max(outer[x], inner2[x]) + w; 
            }
        }
        dfs2(v, x);
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> k;
    foreach(1, n-1, i){
        int x, y, z;
        cin >> x >> y >> z;
        addEdge(x, y, z);
        addEdge(y, x, z);
    }
    foreach(1, k, i){
        int tmp;
        cin >> tmp;
        people[tmp]++;
    }
    dfs(1, 0);
    dfs2(1, 0);
    foreach(1, n, i){
        cout << incost[i] + outcost[i] - max(inner1[i], outer[i]) << '\n';
    }
}