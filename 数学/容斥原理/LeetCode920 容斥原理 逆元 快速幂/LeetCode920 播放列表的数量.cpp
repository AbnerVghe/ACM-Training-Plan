#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 110, MOD = 1e9+7;
int fac[N], inv[N];

int power(int x, int a){
    int ans = 1;
    while(a){
        if(a & 1) ans = ((ll)ans * x) % MOD;
        x = ((ll)x * x) % MOD;
        a >>= 1;
    }
    return ans;
}

void compute(int n){
    fac[1] = 1;
    foreach(2, n, i) fac[i] = (ll)fac[i-1] * i % MOD;
    inv[n] = power(fac[n], MOD-2);
    foreach_sub(n-1, 1, i) inv[i] = (ll)(i+1) * inv[i+1] % MOD;
}

class Solution {
public:
    int numMusicPlaylists(int n, int goal, int k) {
        compute(n);
        int res = (((ll)fac[n] * power(n-k, goal-k))%MOD * inv[n-k])%MOD;
        for(int x = 1, sign = MOD-1; x < n-k; x++, sign = (sign==1) ? MOD-1 : 1){
            res = (res + (((((ll)sign * fac[n])%MOD * power(n-k-x, goal-k))%MOD * inv[x])%MOD * inv[n-k-x])%MOD )%MOD;
        }
        return res;
    }
};