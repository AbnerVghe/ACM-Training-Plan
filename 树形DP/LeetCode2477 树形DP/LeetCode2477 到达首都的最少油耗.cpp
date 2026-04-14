#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

const int N = 1e5+7;
vector<int> p[N];

struct Info{
    int sz;
    ll cost;
};

Info dfs(int x, int fa , int seats){
    int sz = 1;
    ll cost = 0;
    for(auto v: p[x]){
        if(v == fa) continue;

        Info infov = dfs(v, x, seats);
        sz += infov.sz;
        cost += infov.cost + (infov.sz+seats-1)/seats;
    }
    return (Info){sz, cost};
}

class Solution {
public:
    long long minimumFuelCost(vector<vector<int>>& roads, int seats) {
        int n = roads.size()+1;
        foreach(0, n-1, i) p[i].clear();
        for(auto road: roads){
            int u = road[0], v = road[1];
            p[u].push_back(v);
            p[v].push_back(u);
        }
        return dfs(0, -1, seats).cost;
    }
};