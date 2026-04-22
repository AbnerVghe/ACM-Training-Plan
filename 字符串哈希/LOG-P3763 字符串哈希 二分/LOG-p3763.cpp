#include<bits/stdc++.h>
#define ll unsigned long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 1e5+7, base = 499;
ll power[N], hs1[N], hs2[N];
string s1, s2;

int val(char c){
    if(c == 'A') return 1;
    if(c == 'C') return 2;
    if(c == 'G') return 3;
    return 4;
}

void build(string s, ll* hs){
    hs[0] = val(s[0]);
    foreach(1, s.length()-1, i) hs[i] = hs[i-1]*base + val(s[i]);
}

ll compute(ll* hs, int l, int r){
    ll ans = hs[r];
    if(l){
        ans -= hs[l-1] * power[r-l+1];
    }
    return ans;
}

bool check(int l1, int l2, int len){
    int r1 = l1 + len - 1, r2 = l2 + len - 1;
    return compute(hs1, l1, r1) == compute(hs2, l2, r2);
}

bool isSame(int l1, int r1){
    int diff = 0, l2 = 0;
    while(l1 <= r1 && diff <= 3){
        int l = 1, r = r1 - l1 + 1;
        int len = 0;
        while(l <= r){
            int mid = (l+r) / 2;
            if(check(l1, l2, mid)){
                len = mid;
                l = mid + 1;
            }
            else{
                r = mid - 1;
            }
        }
        if(l1 + len <= r1) diff++;
        l1 += len + 1;
        l2 += len + 1;
    }
    return diff <= 3;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    power[0] = 1;
    foreach(1, 1e5, i) power[i] = power[i-1] * base;
    int T;
    cin >> T;
    while(T--){
        cin >> s1 >> s2;
        int n = s1.length(), m = s2.length();
        if(n < m){
            cout << 0 << '\n';
            continue;
        }
        build(s1, hs1);
        build(s2, hs2);
        int ans = 0;
        for(int l = 0, r = m-1; r < n; l++, r++){
            ans += isSame(l, r);
        }
        cout << ans << '\n';
    }
}