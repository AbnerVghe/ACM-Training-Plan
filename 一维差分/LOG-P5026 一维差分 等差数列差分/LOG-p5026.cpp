#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int M = 1e6+7, OFFSET = 30010;
int arr[M+2*OFFSET];

void setVal(int l, int r, int s, int e, int d){
    arr[l+OFFSET] += s;
    arr[l+1+OFFSET] += d-s;
    arr[r+1+OFFSET] -= e+d;
    arr[r+2+OFFSET] += e;
}

void fall(int v, int x){
    setVal(x-3*v+1, x-2*v, 1, v, 1);
    setVal(x-2*v+1, x, v-1, -v, -1);
    setVal(x+1, x+2*v, -v+1, v, 1);
    setVal(x+2*v+1, x+3*v-1, v-1, 1, -1);
}

void build(int m){
    foreach(1, 2, j) foreach(1, m+OFFSET, i){
        arr[i] += arr[i-1];
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;
    foreach(1, n, i){
        int v, x;
        cin >> v >> x;
        fall(v, x);
    }
    build(m);
    for(int i = OFFSET+1, j = 1; j <= m; i++, j++){
        cout << arr[i] << ' ';
    }
}