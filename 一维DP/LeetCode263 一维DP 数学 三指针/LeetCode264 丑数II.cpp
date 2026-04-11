#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 1700;

int dp[N];

class Solution {
public:
    int nthUglyNumber(int n) {
        dp[1] = 1;
        for(int i = 2, i2 = 1, i3 = 1, i5 = 1, cur; i <= n; i++){
            int a, b, c;
            a = dp[i2] * 2;
            b = dp[i3] * 3;
            c = dp[i5] * 5;
            cur = min(a, min(b, c));
            dp[i] = cur;
            if(a == cur) i2++;
            if(b == cur) i3++;
            if(c == cur) i5++;
        }
        return dp[n];
    }
};

signed main(){
    Solution slu;
    cout << slu.nthUglyNumber(7);
}