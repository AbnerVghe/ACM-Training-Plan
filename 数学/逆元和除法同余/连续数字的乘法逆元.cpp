#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 3e6+7;
int inv[N];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, p;
    cin >> n >> p;
    inv[1] = 1;
    cout << 1 << '\n';
    foreach(2, n, i){
        inv[i] = p-(ll)inv[p%i]*(p/i)%p;
        cout << inv[i] << '\n';
    }
}