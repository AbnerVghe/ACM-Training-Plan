#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 1e5+7;
int a[N];
int END[N];
int lis[N];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    foreach(1, n, i) cin >> a[i];
    int len = 0;
    int maxn = 0;
    foreach_sub(n, 1, i){
        int pos = lower_bound(END+1, END+len+1, a[i]) - END;
        if(pos == len){
            END[++len] = a[i];
            lis[i] = len;
            maxn = max(maxn, len);
        }
        else{
            END[pos] = a[i];
            lis[i] = pos;
            maxn = max(maxn, pos);
        }
    }
    foreach(1, n, i) cout << lis[i] << ' ';
    cout << '\n';
    vector<int> ans(maxn+1, INF);
    ans[0] = 0;
    foreach(1, n, i){
        if(ans[maxn-lis[i]] < a[i]) ans[maxn-lis[i]+1] = a[i]; 
    }
    foreach(1, maxn, i) cout << ans[i] << ' ';
}