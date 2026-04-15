#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

vector<int> dgts;
int cnt[12];

class Solution {
public:
    int f1(vector<int>& dgts, int n, int offset, int len, bool free, bool fix){//普通版
        if(!len) return fix;

        int ans = 0;
        int cur = n / offset % 10;
        if(!fix) ans += f1(dgts, n, offset/10, len-1, 1, 0);
        if(!free){
            for(auto dgt: dgts){
                if(dgt < cur) ans += f1(dgts, n, offset/10, len-1, 1, 1);
                else if(dgt == cur) ans += f1(dgts, n, offset/10, len-1, 0, 1);
                else break;
            }
        }
        else ans += dgts.size() * f1(dgts, n, offset/10, len-1, 1, 1);
        return ans;
    }

    int atMostNGivenDigitSet1(vector<string>& digits, int n) {
        dgts.clear();
        for(auto digit: digits) dgts.push_back(digit[0] - '0');
    
        int tmp = n / 10;
        int len = 1, offset = 1;
        while(tmp > 0){
            tmp /= 10;
            len++;
            offset *= 10;
        }
        return f1(dgts, n, offset, len, 0, 0);
    }

    int f2(vector<int>& dgts, int n, int offset, int len){//加速版
        if(!len) return 1;

        int ans = 0;
        int cur = n / offset % 10;
        for(auto dgt: dgts){
            if(dgt < cur) ans += cnt[len-1];
            else if(dgt == cur) ans += f2(dgts, n, offset/10, len-1);
            else break; 
        }
        return ans;
    }

    int atMostNGivenDigitSet2(vector<string>& digits, int n) {
        dgts.clear();
        for(auto digit: digits) dgts.push_back(digit[0] - '0');
    
        int tmp = n / 10;
        int len = 1, offset = 1;
        while(tmp > 0){
            tmp /= 10;
            len++;
            offset *= 10;
        }
        
        int m = digits.size();
        cnt[0] = 1;
        int ans = 0;
        for(int k = 1, i = m; k < len; k++, i *= m){
            cnt[k] = i;
            ans += i;
        }
        return ans + f2(dgts, n, offset, len);
    }
};