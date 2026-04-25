#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 2e4+7;
int b[N];

class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        foreach(1, n, i){
            b[i] = 0;
        }
        for(auto booking: bookings){
            int s = booking[0], e = booking[1], v = booking[2];
            b[s] += v, b[e+1] -= v; 
        }
        vector<int> ans(n);
        ans[0] = b[1];
        foreach(1, n-1, i){
            ans[i] = ans[i-1] + b[i+1];
        }
        return ans;
    }
};