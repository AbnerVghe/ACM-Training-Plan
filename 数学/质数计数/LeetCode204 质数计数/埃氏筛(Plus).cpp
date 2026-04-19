#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

//只计数，还能优化成这样

const int N = 5e6+7;
bool noPrime[N];

class Solution {
public:
    int countPrimes(int n) {
        n--;
        if(n <= 1) return 0;
        
        foreach(2, n, i) noPrime[i] = 0;
        int cnt = (n+1) / 2;//预估质数数量，忽略偶数
        for(int i = 3; i <= n; i += 2){
            if(!noPrime[i]){
                for(ll j = i; i * j <= n; j += 2){
                    if(!noPrime[i*j]){
                        noPrime[i*j] = 1;
                        cnt--;//除去合数
                    }
                }
            }
        }
        return cnt;
    }
};