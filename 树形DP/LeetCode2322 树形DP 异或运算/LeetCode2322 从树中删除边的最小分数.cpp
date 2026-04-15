#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

const int N = 1010;
int dfn[N], sz[N], sum[N];
int cntD;
vector<int> p[N];

void dfs(vector<int>& nums, int x, int fa){
    int id = ++cntD;
    dfn[x] = id;
    sz[id] = 1;
    sum[id] = nums[x];
    for(auto v: p[x]){
        if(v == fa) continue;

        dfs(nums, v, x);
        sz[id] += sz[dfn[v]];
        sum[id] ^= sum[dfn[v]]; 
    }
}

class Solution {
public:
    int minimumScore(vector<int>& nums, vector<vector<int>>& edges) {
        int n = nums.size();
        foreach(0, n-1, i) p[i].clear();
        cntD = 0;
        for(auto edge: edges){
            int u = edge[0], v = edge[1];
            p[u].push_back(v);
            p[v].push_back(u);
        }
        dfs(nums, 0, -1);
        int ans = INF;
        foreach(2, n, i) foreach(i+1, n, j){
            int sum1, sum2, sum3;
            if(j > i + sz[i] - 1){
                sum1 = sum[i], sum2 = sum[j];
                sum3 = sum[1] ^ sum1 ^ sum2;
            }
            else{
                sum1 = sum[j];
                sum2 = sum[i] ^ sum[j];
                sum3 = sum[1] ^ sum[i];
            }
            int maxsum = max(sum1, max(sum2, sum3));
            int minsum = min(sum1, min(sum2, sum3));
            ans = min(ans, maxsum - minsum);
        }
        return ans;
    }
};