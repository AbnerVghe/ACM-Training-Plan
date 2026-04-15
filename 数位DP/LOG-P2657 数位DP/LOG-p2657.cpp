#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 11;
int dp[N][N][2];

void build(int len){
    foreach(1, len, i) foreach(0, 10, j) foreach(0, 1, k){
        dp[i][j][k] = -1;
    }
}

int f(int num, int offset, int len, int pre, bool free){
    if(!len) return 1;

    int cur = (num / offset) % 10;
    if(dp[len][pre][free] != -1) return dp[len][pre][free];

    int ans = 0;
    if(!free){
        if(pre == 10){
            ans += f(num, offset/10, len-1, 10, 1);
            foreach(1, cur-1, i){
                ans += f(num, offset/10, len-1, i, 1);
            }
            ans += f(num, offset/10, len-1, cur, 0);
        }
        else{
            foreach(0, 9, i){
                if(i <= pre-2 || i >= pre+2){
                    if(i < cur) ans += f(num, offset/10, len-1, i, 1);
                    else if(i == cur) ans += f(num, offset/10, len-1, cur, 0);
                }
            }
        }
    }
    else{
        if(pre == 10){
            ans += f(num, offset/10, len-1, 10, 1);
            foreach(1, 9, i) ans += f(num, offset/10, len-1, i, 1);
        }
        else{
            foreach(0, 9, i) if(i <= pre-2 || i >= pre+2) ans += f(num, offset/10, len-1, i, 1);
        }
    }
    dp[len][pre][free] = ans;
    return ans;
}

int cnt(int num){
    if(!num) return 1;

    int tmp = num / 10;
    int len = 1, offset = 1;
    while(tmp){
        tmp /= 10;
        len++;
        offset *= 10;
    }
    build(len);
    return f(num, offset, len, 10, 0);
}

signed main(){
    ios::sync_with_stdio();
    cin.tie(0); cout.tie(0);
    
    int a, b;
    cin >> a >> b;
    cout << cnt(b) - cnt(a-1);
}