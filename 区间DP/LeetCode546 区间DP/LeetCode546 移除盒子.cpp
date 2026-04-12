#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 110;
int dp[N][N][N];
int n;

class Solution {
public:
    int f(vector<int>& boxes, int i, int j, int k){
        if(i > j) return 0;
        if(dp[i][j][k]) return dp[i][j][k];
        
        int s = i;
        while(s+1 <= j && boxes[i] == boxes[s+1]) s++;
        int cnt = k + s - i + 1;
        int ans = cnt * cnt + f(boxes, s+1, j, 0);
        foreach(s+2, j, m){
            if(boxes[i] == boxes[m] && boxes[m-1] != boxes[m]){
                ans = max(ans, f(boxes, s+1, m-1, 0) + f(boxes, m, j, cnt));
            }
        }
        dp[i][j][k] = ans;
        return ans;
    }

    int removeBoxes(vector<int>& boxes) {
        n = boxes.size();
        memset(dp, 0, sizeof dp);
        return f(boxes, 0, n-1, 0);
    }
};