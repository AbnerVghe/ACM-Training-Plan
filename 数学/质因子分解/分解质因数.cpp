#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

//复杂度O(sqrt(n))

void f(int n){
    for(int i = 2; i * i <= n; i++){
        if(n % i == 0){
            cout << i << ' ';
            while(n % i == 0) n /= i;//往下榨
        }
    }
    if(n > 1) cout << n << ' ';//还没榨干，自己是最后一块质数碎片
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    f(n);
}