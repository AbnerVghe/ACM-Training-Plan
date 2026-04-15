/*#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

class Solution {
public:
    int numDupDigitsAtMostN(int n){

    }
};*/

#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

int cnt[12];

class Solution {
public:
    int numDupDigitsAtMostN(int n) {
        int tmp = n / 10;
        int len = 1;
        int offset = 1;
        while(tmp > 0){
            tmp /= 10;
            len++;
            offset *= 10;
        }

        int ans = 0;
        cnt[0] = 1;
        for(int i = 1, k = 10 - len + 1; i < len; i++, k++){
            cnt[i] = cnt[i-1] * k;
        }
        if(len >= 2){
            ans = 9;
            for(int i = 2, a = 9, b = 9; i < len; i++, b--){
                a *= b;
                ans += a;
            }
        }
        int first = n / offset;
        ans += (first-1) * cnt[len-1];
        ans += f(n, offset/10, len-1, 1<<first);

        return n-ans;
    }

    int f(int n, int offset, int len, int status){
        if(!len) return 1;

        int first = (n / offset) % 10;
        int ans = 0;
        foreach(0, first-1, cur){
            if(!(status & (1 << cur))) ans += cnt[len-1];
        }
        if(!(status & (1 << first))) ans += f(n, offset/10, len-1, status | (1 << first));
        return ans;
    }
};