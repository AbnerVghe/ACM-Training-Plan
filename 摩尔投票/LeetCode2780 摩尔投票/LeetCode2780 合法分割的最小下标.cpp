#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

class Solution {
public:
    int minimumIndex(vector<int>& nums) {
        int n = nums.size();
        int cand, hp = 0;
        for(auto num: nums){
            if(!hp){
                cand = num;
                hp = 1;
            }
            else{
                if(cand == num) hp++;
                else hp--;
            }
        }
        hp = 0;
        for(auto num: nums){
            if(cand == num) hp++;
        }
        
        for(int i = 0, lc = 0, rc = hp; i < n; i++){
            if(cand == nums[i]){
                lc++;
                rc--;
            }
            if(lc > (i+1)/2 && rc > (n-i-1)/2){
                return i;
            }
        }
        return -1;
    }
};