#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 60;
int dmin[N][N], dmax[N][N];//dmin[i][j]=t,i-j>=t

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n, a, b;
    cin >> n >> a >> b;
    foreach(1, n, i){
        foreach(1, n, j){
            char s;
            cin >> s;
            if(s == '+'){
                dmin[i][j] = 1;
                dmax[i][j] = 2;
            }
            else if(s == '-'){
                dmin[i][j] = -2;
                dmax[i][j] = -1;
            }
            else if(s == '='){
                dmin[i][j] = dmax[i][j] = 0;
            }
            else{
                dmin[i][j] = -2;
                dmax[i][j] = 2;
            }
        }
    }
    foreach(1, n, i){
        dmin[i][i] = dmax[i][i] = 0;
    }
    foreach(1, n, k){
        foreach(1, n, i){
            foreach(1, n, j){
                dmin[i][j] = max(dmin[i][j], dmin[i][k]+dmin[k][j]);
                dmax[i][j] = min(dmax[i][j], dmax[i][k]+dmax[k][j]);
            }
        }
    }
    int ans1 = 0, ans2 = 0, ans3 = 0;
    foreach(2, n, i){
        foreach(1, i-1, j){
            if(i == a || i == b || j == a || j == b) continue;
            if(dmin[a][i] > dmax[j][b] || dmin[a][j] > dmax[i][b]){
                ans1++;
            }
            if(dmax[a][i] < dmin[j][b] || dmax[a][j] < dmin[i][b]){
                ans3++;
            }
            if(dmin[a][i] == dmax[a][i] && dmin[j][b] == dmax[j][b] && dmin[a][i] == dmin[j][b]){
                ans2++;
            }
            else if(dmin[j][a] == dmax[j][a] && dmin[b][i] == dmax[b][i] && dmin[j][a] == dmin[b][i]){
                ans2++;
            }
        }
    }
    cout << ans1 << ' ' << ans2 << ' ' << ans3;
}