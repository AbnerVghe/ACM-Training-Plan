#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

//O(logn * k^3)

vector<vector<int>> multipy(vector<vector<int>> A, vector<vector<int>> B){
    int n = A.size(), m = B[0].size(), k = A[0].size();
    vector<vector<int>> mtx(n, vector<int>(m, 0));
    foreach(0, n-1, i) foreach(0, m-1, j) foreach(0, k-1, c){
        mtx[i][j] += A[i][c] * B[c][j];
    }
    return mtx;
}

vector<vector<int>> power(vector<vector<int>> A, int p){
    int n = A.size();
    vector<vector<int>> ans(n, vector<int>(n, 0));
    foreach(0, n-1, i) ans[i][i] = 1;//单位矩阵
    while(p > 0){
        if(p & 1){
            ans = multipy(ans, A);
        }
        A = multipy(A, A);
        p >>= 1;
    }
    return ans;
}

void print(vector<vector<int>> A){
    int n = A.size(), m = A[0].size();
    foreach(0, n-1, i){
        foreach(0, m-1, j){
            cout << A[i][j] << ' ';
        }
        cout << '\n';
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    vector<vector<int>> A = {{1, 2}, {3, 4}};
    print(power(A, 5));
}