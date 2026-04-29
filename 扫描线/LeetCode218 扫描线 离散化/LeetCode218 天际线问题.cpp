#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

typedef pair<int, int> pii;

const int N = 1e4+7, M = 3e4+7;
struct BD{
    int L, R, H;
}bd[M];

int b[M];
int pos;

int Rank(int val){
    return lower_bound(b+1, b+pos+1, val) - b;
}

bool cmp(BD A, BD B){
    return A.L < B.L;
}

int h[M];
priority_queue<pii> Q; 

class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        int cnt = 0;
        for(auto building: buildings){
            b[++cnt] = building[0];
            b[++cnt] = building[1]-1;
            b[++cnt] = building[1];
        }
        sort(b+1, b+cnt+1);
        pos = unique(b+1, b+cnt+1) - (b+1);
        int n = buildings.size();
        foreach(1, n, i){
            auto x = buildings[i-1];
            int L = Rank(x[0]), R = Rank(x[1]-1), H = x[2];
            bd[i] = {L, R, H};
        }
        sort(bd+1, bd+n+1, cmp);
        while(Q.size()) Q.pop();
        int j = 1;
        foreach(1, pos, i){
            while(j <= n && bd[j].L <= i){
                Q.push({bd[j].H, bd[j].R});
                j++;
            }
            bool ok = 0;
            while(Q.size()){
                auto U = Q.top();
                int H = U.first, R = U.second;
                if(R < i){
                    Q.pop();
                    continue;
                }
                h[i] = H;
                ok = 1;
                break;
            }
            if(!ok) h[i] = 0;
        }
        vector<vector<int>> ans;
        int now = 0;
        foreach(1, pos, i){
            if(now != h[i]){
                ans.push_back({b[i], h[i]});
                now = h[i];
            }
        }
        return ans;
    }
};