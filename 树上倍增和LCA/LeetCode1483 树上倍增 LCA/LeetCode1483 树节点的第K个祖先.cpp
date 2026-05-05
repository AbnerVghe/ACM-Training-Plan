#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 5e4+7, LMT = 20;
vector<int> p[N];
int dep[N];
int st[N][LMT];
int power;

class TreeAncestor {
public:
    int log2(int n){
        int ans = 0;
        while((1<<ans) <= (n>>1)) ans++;
        return ans;
    }

    void dfs(int x, int fa){
        if(x) dep[x] = dep[fa] + 1;
        st[x][0] = fa;
        for(int p = 1; (1 << p) <= dep[x]; p++){
            st[x][p] = st[st[x][p-1]][p-1];
        }
        for(auto v: p[x]){
            dfs(v, x);
        }
    }

    TreeAncestor(int n, vector<int>& parent) {
        power = log2(n);
        foreach(0, n-1, i) p[i].clear();
        foreach(1, n-1, i){
            int v = parent[i];
            p[v].push_back(i);
        }
        dep[0] = 1;
        dfs(0, 0);
    }
    
    int getKthAncestor(int node, int k) {
        if(k >= dep[node]) return -1;
        for(int j = power; j >= 0 && k; j--){
            if(k >= (1 << j)){
                node = st[node][j];
                k -= (1 << j);
            }
        }
        return node;
    }
};

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor* obj = new TreeAncestor(n, parent);
 * int param_1 = obj->getKthAncestor(node,k);
 */