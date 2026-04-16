#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 31;
int cnt[N];

class Solution {
public:
    int f(int i, int num){//数位i与num一样的方案数
        if(i == -1) return 1;
    
        int ans = 0;
        if((num >> i) & 1){
            ans += cnt[i];//i+1位写0，后面随意发挥
            if((num >> (i+1)) & 1){
                return ans;
            }
        }
        ans += f(i-1, num);
        return ans;
    }

    int findIntegers(int n) {
        cnt[0] = 1, cnt[1] = 2;
        foreach(2, 30, i) cnt[i] = cnt[i-1] + cnt[i-2];

        return f(30, n);
    }
};