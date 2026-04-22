#include<bits/stdc++.h>
#define ll unsigned long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 3e4+7, base = 499;
ll power[N], hashVal[N];

ll compute(int l, int r){
    ll ans = hashVal[r];
    if(l){
        ans -= hashVal[l-1]*power[r-l+1];
    }
    return ans;
}

class Solution {
public:
    int repeatedStringMatch(string a, string b) {
        int n = a.length(), m = b.length();
        int k = (m + n - 1) / n;
        string s = "";
        foreach(0, k, i) s += a;
        
        int nn = s.length();
        power[0] = 1;
        foreach(1, nn, i) power[i] = power[i-1] * base;

        hashVal[0] = s[0] - 'a' + 1;
        foreach(1, nn-1, i) hashVal[i] = hashVal[i-1]*base + (s[i] - 'a' + 1);

        ll hs = 0;
        foreach(0, m-1, i) hs = hs*base + (b[i] - 'a' + 1);

        for(int l = 0, r = m-1; r < nn; l++, r++){
            if(compute(l, r) == hs){
                if(r < nn - n) return k;
                else return k+1;
            }            
        }
        return -1;
    }
};