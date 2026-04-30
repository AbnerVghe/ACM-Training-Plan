#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int n = nums.size();
        int cand, hp = 0;
        for(auto num: nums){//高效删除两个不同元素
            if(!hp){
                cand = num;
                hp = 1;
            }
            else{
                if(cand == num){
                    hp++;
                }
                else hp--;
            }
        }
        return cand;
    }
};