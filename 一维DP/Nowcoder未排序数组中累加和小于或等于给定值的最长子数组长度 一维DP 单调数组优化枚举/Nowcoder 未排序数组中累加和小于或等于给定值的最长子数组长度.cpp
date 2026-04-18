#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 1e5+7;
int a[N], minSum[N], minSumEnd[N];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, k;
    cin >> n >> k;
    foreach(1, n, i){
        cin >> a[i];
    }
    minSum[n] = a[n], minSumEnd[n] = n;
    foreach_sub(n-1, 1, i){
        if(minSum[i+1] <= 0){
            minSum[i] = a[i] + minSum[i+1];
            minSumEnd[i] = minSumEnd[i+1];
        }
        else{
            minSum[i] = a[i];
            minSumEnd[i] = i;
        }
    }
    int ans = 0;
    for(int i = 1, sum = 0, end = 1; i <= n; i++){
        while(end <= n && sum + minSum[end] <= k){
            sum += minSum[end];
            end = minSumEnd[end] + 1;
        }
        if(end > i){
            ans = max(ans, end - i);
            sum -= a[i];
        }
        else{
            end = i + 1;
        }
    }
    cout << ans;
}