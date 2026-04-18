#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 1010, MOD = 1e9+7;
const int M = N*N/2;
int dp[M], pre[M];

class Solution {
public:
    int kInversePairs(int n, int k) {
        dp[0] = 1, pre[0] = 1;
        foreach(1, k, i) dp[i] = 0, pre[i] = 1;

        foreach(2, n, i){
            foreach(1, k, j){
                if(i > j){
                    dp[j] = pre[j];
                }
                else{
                    dp[j] = (pre[j] - pre[j-i] + MOD)%MOD;
                }
            }
            foreach(1, k, j){
                pre[j] = (pre[j-1] + dp[j])%MOD;
            }
        }
        return dp[k];
    }
};