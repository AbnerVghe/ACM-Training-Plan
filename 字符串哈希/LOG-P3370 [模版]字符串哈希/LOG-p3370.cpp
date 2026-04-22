#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 1e4+7, base = 1e9+7;
int num[N];

int val(char x){
    if('0' <= x && x <= '9') return x - '0' + 1;
    if('A' <= x && x <= 'Z') return x - 'A' + 11;
    if('a' <= x && x <= 'z') return x - 'a' + 37;
}

ll hashVal(string s){
    ll ans = val(s[0]);
    foreach(1, s.length()-1, i){
        ans = ans * base + val(s[i]);
    }
    return ans;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    int n;
    cin >> n;
    foreach(1, n, i){
        string tmp;
        cin >> tmp;
        num[i] = hashVal(tmp);
    }
    sort(num+1, num+n+1);
    int ans = 1;
    foreach(1, n-1, i){
        if(num[i] != num[i+1]) ans++;
    }
    cout << ans;
}