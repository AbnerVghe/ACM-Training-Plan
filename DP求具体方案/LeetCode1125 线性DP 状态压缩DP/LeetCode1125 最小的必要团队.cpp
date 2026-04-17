#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

int n, m;
vector<int> arr;

int dp[70][(1 << 20)];

class Solution {
public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        int cnt = 0;
        n = people.size(), m = req_skills.size();
        unordered_map<string, int> skills;
        for(auto req_skill: req_skills){
            skills[req_skill] = cnt++;
        }
        arr.clear();
        for(auto person: people){
            int status = 0;
            for(auto i: person){
                if(skills.count(i)){
                    status |= 1 << skills[i];
                }
            }
            arr.push_back(status);
        }

        foreach(0, n, i) foreach(0, (1 << m) -1, j) dp[i][j] = -1;

        vector<int> ans(0);
        int size = f(0, 0);
        for(int i = 0, s = 0; s != (1 << m) - 1; i++){
            if(i+1 == n || dp[i][s] != dp[i+1][s]){
                ans.push_back(i);
                s |= arr[i];
            }
        }
        return ans;
    }

    int f(int i, int status){
        if(status == (1 << m) - 1) return 0;
        if(i == n) return INF;
        if(dp[i][status] != -1) return dp[i][status];

        int p1 = f(i+1, status);
        int p2 = INF;
        int next2 = f(i+1, status | arr[i]);
        if(next2 != INF) p2 = 1 + next2;
        int ans = min(p1, p2);
        dp[i][status] = ans;
        return ans;
    }
};