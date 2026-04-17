#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 210;
int dp[N][N];
string path[N][N];
int a[N], b[N], c[N];

bool compare(string A, string B){//<:0,>:1
    int i = 0, j = 0;
    while(i < A.length() && j < B.length()){
        while(A[i] == ' ') i++;
        while(B[j] == ' ') j++;
        if(A[i] > B[j]) return 1;
        else if(A[i] < B[j]) return 0;
        i++, j++;
    }
    return A.length() > B.length();
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    //cout << compare("1 18", "1 1 3") << ' ' << compare("1 12", "1 123");

    int m, v, n;
    cin >> m >> v >> n;
    foreach(1, n, i){
        cin >> a[i] >> b[i] >> c[i]; 
    }
    foreach(0, m, j) foreach(0, v, k) path[j][k] = "";

    foreach(1, n, i){
        foreach_sub(m, a[i], j){
            foreach_sub(v, b[i], k){
                if(dp[j][k] < dp[j-a[i]][k-b[i]] + c[i]){
                    dp[j][k] = dp[j-a[i]][k-b[i]] + c[i];
                    if(path[j-a[i]][k-b[i]] == "") path[j][k] = to_string(i);
                    else path[j][k] = path[j-a[i]][k-b[i]] + " " + to_string(i);
                }
                else if(dp[j][k] == dp[j-a[i]][k-b[i]] + c[i]){
                    if(compare(path[j][k], path[j-a[i]][k-b[i]]+to_string(i))){
                        path[j][k] = path[j-a[i]][k-b[i]] + " " + to_string(i);
                    }
                }
            }
        }
    }
    cout << dp[m][v] << '\n';
    cout << path[m][v];
}