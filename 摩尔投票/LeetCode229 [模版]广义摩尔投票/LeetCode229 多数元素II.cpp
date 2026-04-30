#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

int cand[10][2];//k-1的大小(k-1个候选人)，以及血量的储存

class Solution {
public:
    void init(int k){
        foreach(1, k, i) cand[i][1] = 0;
    }

    void update(int num, int k){
        foreach(1, k, i){
            if(cand[i][1] > 0 && cand[i][0] == num){
                cand[i][1]++;
                return;
            }
        }
        foreach(1, k, i){
            if(cand[i][1] == 0){
                cand[i][0] = num;
                cand[i][1] = 1;
                return;
            }
        }
        foreach(1, k, i){
            cand[i][1]--;
        }
    }

    vector<int> majorityElement(vector<int>& nums) {
        int n = nums.size();
        int k = 3;
        init(k-1);
        for(auto num: nums){
            update(num, k-1);
        }
        vector<int> ans;
        foreach(1, k-1, i){
            if(!cand[i][1]) continue;
            int cnt = 0;
            for(auto num: nums){
                if(cand[i][0] == num) cnt++;
            }
            if(cnt > n/k) ans.push_back(cand[i][0]);
        }
        return ans;
    }
};