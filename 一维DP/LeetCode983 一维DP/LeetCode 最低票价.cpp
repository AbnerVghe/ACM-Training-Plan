#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 370;
int n;
//int mem[N];
int dp[N];
int duration[3] = {1, 7, 30};

/*int dfs(int i, vector<int>& days, vector<int>& costs){
    if(i >= n) return 0;
    if(mem[i] != INF) return mem[i];
    int j = i, ans = INF;
    foreach(0, 2, k){
        while(j < n && days[i] + duration[k] > days[j]){
            j++;
        }
        ans = min(ans, costs[k] + dfs(j, days, costs));
    }
    mem[i] = ans;
    return ans;
}*/

class Solution {
public:
    /*int mincostTickets(vector<int>& days, vector<int>& costs) {
        n = days.size();
        foreach(0, n, i) mem[i] = INF;
        return dfs(0, days, costs);
    }*/

    int mincostTickets(vector<int>& days, vector<int>& costs) {
        n = days.size();
        foreach(0, n, i) dp[i] = INF;
        dp[n] = 0;
        foreach_sub(n-1, 0, i){
            int j = i;
            foreach(0, 2, k){
                while(j < n && days[i] + duration[k] > days[j]){
                    j++;
                }
                dp[i] = min(dp[i], costs[k]+dp[j]);
            }
        }
        return dp[0];
    }
};

signed main(){
    Solution slu;
    vector<int> days = {1,4,6,7,8,20}, costs = {2,7,15};
    cout << slu.mincostTickets(days, costs);
}