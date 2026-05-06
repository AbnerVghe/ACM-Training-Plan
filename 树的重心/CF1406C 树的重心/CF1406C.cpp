#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 1e5+7;
int sz[N];
vector<int> p[N];
int maxSub[N];
int n;
vector<int> center;

void dfs(int x, int fa){
    sz[x] = 1;
    int tmp = 0;
    for(auto v: p[x]){
        if(v == fa) continue;
        dfs(v, x);
        sz[x] += sz[v];
        tmp = max(tmp, sz[v]);
    }
    tmp = max(tmp, n-sz[x]);
    maxSub[x] = tmp;
}

int leaf;
int leafFa;
void find(int x, int fa){
    for(auto v: p[x]){
        if(v == fa) continue;
        find(v, x);
        return;
    }
    leaf = x;
    leafFa = fa;
}

void clear(){
    foreach(1, n, i){
        p[i].clear();
    }
    center.clear();
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int T;
    cin >> T;
    while(T--){
        cin >> n;
        foreach(1, n-1, i){
            int x, y;
            cin >> x >> y;
            p[x].push_back(y);
            p[y].push_back(x);
        }
        dfs(1, 0);
        foreach(1, n, i){
            if(maxSub[i] <= n/2){
                center.push_back(i);
            }
        }
        int cnt = center.size();
        if(cnt == 1){
            foreach(1, 2, i){
                cout << center[0] << ' ' << p[center[0]][0] << '\n';
            }
        }
        else{
            find(center[1], center[0]);
            cout << leafFa << ' ' << leaf << '\n';
            cout << leaf << ' ' << center[0] << '\n';
        }
        clear();
    }
}