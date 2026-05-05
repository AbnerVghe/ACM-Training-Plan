#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 1e5+7, L = 35;
int st[N][40];
ll stSum[N][40];

class Solution {
public:
    long long getMaxFunctionValue(vector<int>& receiver, long long k) {
        int n = receiver.size();
        foreach(0, n-1, i){
            int v = receiver[i];
            st[i][0] = v;
            stSum[i][0] = v;
        }
        foreach(1, L, j){
            foreach(0, n-1, i){
                st[i][j] = st[st[i][j-1]][j-1];
                stSum[i][j] = stSum[i][j-1] + stSum[st[i][j-1]][j-1];
            }
        }
        ll ans = 0;
        foreach(0, n-1, i){
            int x = i;
            ll tmp = x;
            foreach_sub(L, 0, j){
                if((k>>j)&1){
                    tmp += stSum[x][j];
                    x = st[x][j];
                }
            }
            ans = max(ans, tmp);
        }
        return ans;
    }
};