#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

int power(int a, int b, int p){
    int ans = 1;
    while(b > 0){
        if(b & 1){
            ans = ((ll)ans * a) % p;
        }
        a = (ll)a * a % p;
        b >>= 1;
    }
    return ans;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int a, b, p;
    cin >> a >> b >> p;
    cout << a << '^' << b << " mod " << p << '=' << power(a, b, p);
}