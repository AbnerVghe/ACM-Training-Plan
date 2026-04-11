#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 110;

int zeros, ones;
int dp[N][N];

void findNum(string str){
    zeros = 0, ones = 0;
    for(auto c: str){
        if(c == '0') zeros++;
        else ones++;
    }
}

class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        foreach(0, m, i) foreach(0, n, j) dp[i][j] = 0;
        for(auto str: strs){
            findNum(str);
            foreach_sub(m, zeros, z) foreach_sub(n, ones, o){
                dp[z][o] = max(dp[z][o], 1+dp[z-zeros][o-ones]);
            }
        }
        return dp[m][n];
    }
};

signed main(){
    Solution slu;
    vector<string> strs = {"10", "0", "1"};
    int m = 1, n = 1;
    cout << slu.findMaxForm(strs, m, n);
}