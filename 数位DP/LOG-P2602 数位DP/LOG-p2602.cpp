#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

int cnt(int num, int d){
    if(!num) return 0;

    int tmp = num / 10;
    int len = 1;
    while(tmp){
        tmp /= 10;
        len++;
    }
    int ans = 0;
    for(int Left = num/10, Right = 1, cur, i = 1; i <= len; i++, Left /= 10, Right *= 10){
        cur = num / Right % 10;
        if(d){
            if(cur < d){
                ans += Left * Right;
            }
            else if(cur > d){
                ans += (Left+1) * Right; 
            }
            else{//cur == d
                ans += Left * Right;
                ans += num % Right + 1;
            }
        }
        else{
            if(cur > d){
                ans += Left * Right;
            }
            else{//cur == d
                ans += (Left-1) * Right;
                ans += num % Right + 1;
            }
        }
    }
    return ans;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int a, b;
    cin >> a >> b;
    foreach(0, 9, i){
        cout << cnt(b, i) - cnt(a-1, i) << ' ';
    }
}