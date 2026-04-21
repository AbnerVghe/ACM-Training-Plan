#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        int lmt = 0;
        int maxn = 0;
        for(auto num: nums){
            maxn = max(maxn, num);
        }
        foreach_sub(30, 0, i){
            if((maxn >> i)&1){
                lmt = i;
                break;
            }
        }
        int ans = 0;
        unordered_set<int> hs;
        foreach_sub(lmt, 0, i){
            int better = ans | (1 << i);
            hs.clear();
            for(auto num: nums){
                num = (num >> i) << i;
                hs.insert(num);
                if(hs.count(better ^ num)){
                    ans = better;
                    break;
                }
            }   
        }
        return ans;
    }
};