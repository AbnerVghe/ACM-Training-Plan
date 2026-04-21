#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 1e5+7;
int cnt[N], power[N], dp[N];

const int MOD = 1e9+7;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    foreach(1, n, i){
        int tmp;
        cin >> tmp;
        cnt[tmp]++;
    }

    power[0] = 1;
    foreach(1, 1e5, i){
        power[i] = power[i-1] * 2 % MOD;
    }

    foreach_sub(1e5, 1, i){
        int count = 0, deli = 0;
        //if(!cnt[i]) continue;
        for(int j = i; j <= 1e5; j += i){
            count += cnt[j];
            deli = (deli + dp[j]) % MOD;
        }
        dp[i] = ((power[count] - 1 + MOD)%MOD - deli + MOD)%MOD;
    }

    cout << dp[1];
}