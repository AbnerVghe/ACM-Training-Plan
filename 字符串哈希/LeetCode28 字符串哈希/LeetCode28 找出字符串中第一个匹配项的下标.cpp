#include<bits/stdc++.h>
#define ll unsigned long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int base = 499, N = 1e4+7;
ll power[N];
ll hashVal[N];

ll compute(int l, int r){
    ll ans = hashVal[r];
    if(l){
        ans -= hashVal[l-1] * power[r - l + 1];
    } 
    return ans;
}

class Solution {
public:
    int strStr(string haystack, string needle) {
        int n = haystack.length();
        power[0] = 1;
        foreach(1, n-1, i){
            power[i] = power[i-1] * base;
        }

        hashVal[0] = haystack[0] - 'a' + 1;
        foreach(1, n-1, i){
            hashVal[i] = hashVal[i-1] * base + haystack[i] - 'a' + 1;
        }
        int m = needle.length();
        int ans = -1;
        ll com = 0;
        foreach(0, m-1, i){
            com = com * base + (needle[i] - 'a' + 1);
        }
        foreach(0, n-m, i){
            int r = i + m - 1;
            if(compute(i,r) == com){
                ans = i;
                break;
            }
        }
        return ans;
    }
};

signed main(){
    string haystack = "leetcode", needle = "co";
    Solution slu;
    cout << slu.strStr(haystack, needle);
}