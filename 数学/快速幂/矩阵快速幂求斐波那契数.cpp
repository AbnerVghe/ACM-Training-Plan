#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

typedef vector<int> vi;
typedef vector<vector<int>> vvi;

vvi multipy(vvi A, vvi B){
    int n = A.size(), m = B[0].size(), k = A[0].size();
    vvi C;
    C.assign(n, vi(m));
    foreach(0, n-1, i) foreach(0, m-1, j) foreach(0, k-1, c){
        C[i][j] += A[i][c] * B[c][j];
    }
    return C;
}  

vvi power(vvi A, int p){
    int n = A.size();
    vvi ans;
    ans.assign(n, vi(n, 0));
    foreach(0, n-1, i) ans[i][i] = 1;
    while(p){
        if(p & 1) ans = multipy(ans, A);
        A = multipy(A, A);
        p >>= 1;
    }
    return ans;
}

class Solution {
public:
    int fib(int n) {
        if(n == 0) return 0;
        
        vvi init = {{1, 0}};
        vvi mtx = {{1, 1}, {1, 0}};
        vvi ans = multipy(init, power(mtx, n-1));
        return ans[0][0];
    }
};