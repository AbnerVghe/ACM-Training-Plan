#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int MOD = 1e9+7;

int dp[30][410][2];
int len, maxn, minn;
string num;

class Solution {
public:
    void build(){
        foreach(0, len, i) foreach(0, maxn, j) foreach(0, 1, k){
            dp[i][j][k] = -1;
        }
    }

    int f(int i, int sum, bool free){
        if(sum > maxn || sum + (len-i) * 9 < minn) return 0;
        if(i == len) return 1;
        if(dp[i][sum][free] != -1) return dp[i][sum][free];

        int cur = num[i] - '0';
        int ans = 0;
        if(!free){
            foreach(0, cur-1, pick){
                ans = (ans + f(i+1, sum+pick, 1)) % MOD;
            }
            ans = (ans + f(i+1, sum+cur, 0)) % MOD;
        }
        else{
            foreach(0, 9, pick) ans = (ans + f(i+1, sum+pick, 1)) % MOD;
        }
        dp[i][sum][free] = ans;
        return ans;
    }

    int count(string num1, string num2, int min_sum, int max_sum) {
        maxn = max_sum;
        minn = min_sum;
        len = num1.length();
        num = num1;
        build();
        int ans1 = f(0, 0, 0);
        len = num2.length();
        num = num2;
        build();
        int ans2 = f(0, 0, 0);
        int ans = (ans2 - ans1 + MOD) % MOD;
        ans = (ans + check(num1)) % MOD;
        return ans;
    }

    bool check(string num){
        int sum = 0;
        for(auto cur: num){
            sum += cur - '0';
            if(sum > maxn) return 0; 
        }
        if(sum < minn) return 0;
        return 1;
    }
};