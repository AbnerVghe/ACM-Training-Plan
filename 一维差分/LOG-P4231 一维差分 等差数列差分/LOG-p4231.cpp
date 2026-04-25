#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 1e7+7;
int b[N];
int n;

void setVal(int l, int r, int s, int e, int d){
    b[l] += s;
    b[l+1] += d-s;
    b[r+1] -= e+d;
    b[r+2] += e;
}

void build(){
    foreach(1, 2, j) foreach(1, n, i) b[i] += b[i-1];
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int m;
    cin >> n >> m;
    foreach(1, m, i){
        int l, r, s, e, d;
        cin >> l >> r >> s >> e;
        if(s != e) d = (e-s) / (r-l);
        else d = 0;
        setVal(l, r, s, e, d);
    }
    build();
    int ans = 0, maxn = 0;
    foreach(1, n, i){
        maxn = max(maxn, b[i]);
        ans ^= b[i];
    }
    cout << ans << ' ' << maxn;
}