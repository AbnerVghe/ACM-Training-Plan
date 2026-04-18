#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 5e4+7;

int dp[N];
struct Job{
    int start, end, money;
}job[N];

bool cmp(Job A, Job B){
    return A.end < B.end;
}

int find(int R){
    int l = 1, r = R-1;
    while(l < r){
        int mid = (l+r+1) / 2;
        if(job[mid].end <= job[R].start) l = mid;
        else r = mid-1;
    }
    return l;
}

class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        foreach(1, n, i){
            job[i] = (Job){startTime[i-1], endTime[i-1], profit[i-1]};
        }
        sort(job+1, job+n+1, cmp);
        dp[1] = job[1].money;
        foreach(2, n, i){
            int start = job[i].start;
            dp[i] = job[i].money;
            if(start >= job[1].end){
                dp[i] += dp[find(i)];
            }
            dp[i] = max(dp[i], dp[i-1]);
        }
        return dp[n];
    }
};