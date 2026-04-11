#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 45;
int a[N];

void dfs(int i, int r, int val, vector<int>& vec){
    if(i > r){
        vec.push_back(val);
        return;
    }
    dfs(i+1, r, val+a[i], vec);//choose it
    dfs(i+1, r, val, vec);//do not
}

class Solution {
public:
    int minAbsDifference(vector<int>& nums, int goal) {
        int n = nums.size();
        int maxN = 0, minN = 0;
        for(auto x: nums){
            if(x >= 0) maxN += x;
            else minN += x;
        }
        if(goal > maxN) return abs(goal-maxN);
        if(goal < minN) return abs(goal-minN);

        foreach(1, n, i){
            a[i] = nums[i-1];
        }
        vector<int> vec1, vec2;
        dfs(1, n >> 1, 0, vec1);
        dfs((n >> 1)+1, n, 0, vec2);
        
        sort(vec1.begin(), vec1.end());
        sort(vec2.begin(), vec2.end());
        
        reverse(vec2.begin(), vec2.end());

        /*for(auto x: vec1) cout << x << ' ';
        cout << '\n';
        for(auto x: vec2) cout << x << ' ';
        cout << '\n';*/

        int l, r, ans = abs(goal);
        int n1 = vec1.size(), n2 = vec2.size();
        for(l = r = 0; l < n1 && r < n2; l++){
            while(r < n2-1 && abs(goal - vec1[l] - vec2[r+1]) <= abs(goal - vec1[l] - vec2[r])) r++;
            ans = min(ans, abs(goal - vec1[l] - vec2[r]));
        }
        return ans;
    }

};

signed main(){
    Solution slu;
    vector<int> nums = {5, -7, 3, 5};
    cout << slu.minAbsDifference(nums, 6);
}