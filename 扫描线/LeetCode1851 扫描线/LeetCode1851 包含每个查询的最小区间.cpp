#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 1e5+7;

struct Qs{
    int id, start;
}qs[N];

struct Itv{
    int len, over;
    bool operator < (const Itv &A) const{
        return len > A.len;
    }
};

priority_queue<Itv> Q;

bool cmp(Qs A, Qs B){
    return A.start < B.start;
}

bool cmp2(vector<int>&A, vector<int>&B){
    return A[0] < B[0];
}

class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        while(Q.size()) Q.pop();
        sort(intervals.begin(), intervals.end(), cmp2);
        int n = intervals.size();
        int m = queries.size();
        foreach(0, m-1, i){
            int start = queries[i];
            qs[i] = {i, start};
        }
        sort(qs, qs+m, cmp);
        vector<int> ans(m);
        int j = 0;
        foreach(0, m-1, i){
            while(j < n && intervals[j][0] <= qs[i].start){
                int l = intervals[j][0], r = intervals[j][1];
                j++;
                int len = r - l + 1;
                Q.push({len, r});
            }
            bool ok = 0;
            while(Q.size()){
                auto U = Q.top();
                int len = U.len, over = U.over;
                if(qs[i].start > over){
                    Q.pop();
                    continue;
                }

                ans[qs[i].id] = len;
                ok = 1;
                break;
            }
            if(!ok) ans[qs[i].id] = -1;
        }
        return ans;
    }
};