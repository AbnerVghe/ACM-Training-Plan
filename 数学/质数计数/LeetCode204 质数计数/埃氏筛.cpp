#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 5e6+7;
bool noPrime[N];

class Solution {
public:
    int countPrimes(int n) {
        n--;
        noPrime[0] = noPrime[1] = 1;
        foreach(2, n, i) noPrime[i] = 0;
        int cnt = 0;
        foreach(2, n, i){
            if(!noPrime[i]){
                cnt++;
                for(int j = 2; i * j <= n; j++){
                    noPrime[i * j] = 1;
                }
            }
        } 
        return cnt;
    }
};