#include<bits/stdc++.h>
#define ll long long
#define INF 0x3f3f3f3f
using namespace std;

const int N = 2e5+7;
const int T = N * 40;
int arr[N], pos[N];
int root[N], Left[T], Right[T], firstSz[T], cnt;
int n, m;

int build(int l, int r){
    int rt = ++cnt;
    firstSz[rt] = 0;
    if(l < r){
        int mid = (l + r) >> 1;
        Left[rt] = build(l, mid);
        Right[rt] = build(mid+1, r);
    }
    return rt;
}

int update(int x, int v, int l, int r, int p){
    int rt = ++cnt;
    Left[rt] = Left[p];
    Right[rt] = Right[p];
    firstSz[rt] = firstSz[p] + v;
    if(l < r){
        int mid = (l + r) >> 1;
        if(x <= mid) Left[rt] = update(x, v, l, mid, Left[rt]);
        else Right[rt] = update(x, v, mid+1, r, Right[rt]);
    }
    return rt;
}

int querySz(int L, int R, int l, int r, int p){
    if(L <= l && r <= R){
        return firstSz[p];
    }
    int mid = (l + r) >> 1;
    int ans = 0;
    if(L <= mid) ans += querySz(L, R, l, mid, Left[p]);
    if(R > mid) ans += querySz(L, R, mid+1, r, Right[p]);
    return ans;
}

int queryKth(int k, int l, int r, int p){
    if(l == r) return l;
    int mid = (l + r) >> 1;
    int lsz = firstSz[Left[p]];
    if(lsz >= k) return queryKth(k, l, mid, Left[p]);
    else return queryKth(k-lsz, mid+1, r, Right[p]);
}

int CNT = 0;

void solve(){
    cnt = 0;
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> arr[i];
    }
    root[n+1] = build(1, n);
    for(int i = 1; i <= n; i++){
        pos[i] = 0;
    }
    for(int i = n; i >= 1; i--){
        if(!pos[arr[i]]){
            root[i] = update(i, 1, 1, n, root[i+1]);
        }
        else{
            int tmp = update(pos[arr[i]], -1, 1, n, root[i+1]);
            root[i] = update(i, 1, 1, n, tmp);
        }
        pos[arr[i]] = i;
    }
    cout << "Case #" << ++CNT << ": ";
    int lastAns = 0;
    while(m--){
        int l, r, a, b;
        cin >> l >> r;
        a = (l+lastAns)%n+1;
        b = (r+lastAns)%n+1;
        l = min(a, b);
        r = max(a, b);
        int sz = (querySz(l, r, 1, n, root[l])+1) / 2;
        lastAns = queryKth(sz, 1, n, root[l]);
        cout << lastAns << ' ';
    }
    cout << '\n';
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int Tt;
    cin >> Tt;
    while(Tt--){
        solve();
    }
}