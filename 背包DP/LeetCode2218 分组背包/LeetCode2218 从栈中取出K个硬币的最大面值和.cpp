#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

const int N = 2010;
int dp[N];//考虑前i个组，操作不超过k次最大面值和(=进行了k次，根据贪心，越多越好)

class Solution {
public:
    int maxValueOfCoins(vector<vector<int>>& piles, int k) {
        //int n = piles.size();
        foreach(0, k, i) dp[i] = 0;
        //dp[0] = 0;
        for(auto pile: piles){
            foreach_sub(k, 1, j){
                int sum = 0, v = 0;
                foreach(1, pile.size(), i){
                    sum += pile[i-1], v++;
                    if(j - v >= 0){
                        dp[j] = max(dp[j], dp[j-v]+sum);
                    }
                    else break;
                }
            }
        }
        return dp[k];
    }
};