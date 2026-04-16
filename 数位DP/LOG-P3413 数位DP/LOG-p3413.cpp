#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int MOD = 1e9+7, N = 1010;
int dp[N][12][12][2];

string num;
int len;

void build(){
    foreach(0, len, i) foreach(0, 10, j) foreach(0, 10, k) foreach(0, 1, b){
        dp[i][j][k][b] = -1;
    }
}

int f(int i, int p, int pp, bool free){
    if(i == len) return 1;
    if(dp[i][p][pp][free] != -1) return dp[i][p][pp][free];

    int ans = 0;
    if(!free){
        if(p == 10){
            ans = (ans + f(i+1, 10, 10, 1)) % MOD;
            foreach(1, num[i]-'0'-1, cur){
                ans = (ans + f(i+1, cur, 10, 1)) % MOD;
            }
            ans = (ans + f(i+1, num[i]-'0', 10, 0)) % MOD;
        }
        else{
            foreach(0, num[i]-'0'-1, cur){
                if(cur != p && cur != pp){
                    ans = (ans + f(i+1, cur, p, 1)) % MOD;
                }
            }
            if(num[i]-'0' != p && num[i]-'0' != pp){
                ans = (ans + f(i+1, num[i]-'0', p, 0)) % MOD;
            }
        }
    }
    else{
        if(p == 10){
            ans = (ans + f(i+1, 10, 10, 1)) % MOD;
            foreach(1, 9, cur) ans = (ans + f(i+1, cur, 10, 1)) % MOD;
        }
        else{
            foreach(0, 9, cur){
                if(cur != p && cur != pp){
                    ans = (ans + f(i+1, cur, p, 1)) % MOD;
                }
            }
        }
    }
    dp[i][p][pp][free] = ans;
    return ans;
}

bool check(){
    foreach(1, len-1, i){
        if(num[i-1] == num[i]) return 1;
        if(i>=2 && num[i-2] == num[i]) return 1;
    }
    return 0;
}

int cnt(string s){
    num = s;
    len = s.length();
    build();
    int nom = f(0, 10, 10, 0);
    int all = 0;
    foreach(0, len-1, i){
        all = (all * 10) % MOD;
        all = (all + (num[i]-'0') % MOD) % MOD;
    }
    return (all - nom + MOD) % MOD;
}

signed main(){
    ios::sync_with_stdio();
    cin.tie(0); cout.tie(0);
    
    string l, r;
    cin >> l >> r;
    int cntr = cnt(r);
    int cntl = cnt(l);
    cout << (cntr - cntl + check() + MOD) % MOD;
}