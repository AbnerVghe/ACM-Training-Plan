#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int MOD = 1e9+7;

int power(int a, int b, int p){
    int ans = 1;
    while(b > 0){
        if(b & 1){
            ans = ((ll)ans * a) % p;
        }
        a = (ll)a * a % p;
        b >>= 1;
    }
    return ans;
}

int compute(int a, int b){
    int inv = power(b, MOD-2, MOD);
    return ((a%MOD) * inv) % MOD;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    
}