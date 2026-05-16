#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 2e5+7;
const int T = N * 23;
int root[N], arr[N], lateLeft[T], Left[T], Right[T], cnt;

int build(int l, int r){
    int rt = ++cnt;
    lateLeft[rt] = 0;
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
    lateLeft[rt] = lateLeft[p];
    if(l == r){
        lateLeft[rt] = v;
    }
    else{
        int mid = (l + r) >> 1;
        if(x <= mid){
            Left[rt] = update(x, v, l, mid, Left[rt]);
        }
        else Right[rt] = update(x, v, mid+1, r, Right[rt]);
        lateLeft[rt] = min(lateLeft[Left[rt]], lateLeft[Right[rt]]);
    }
    return rt;
}

int query(int pos, int l, int r, int p){
    if(l == r) return l;
    int mid = (l + r) >> 1;
    if(lateLeft[Left[p]] < pos){
        return query(pos, l, mid, Left[p]);
    }
    else{
        return query(pos, mid+1, r, Right[p]);
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n, m;
    cin >> n >> m;
    foreach(1, n, i){
        cin >> arr[i];
    }
    root[0] = build(0, n);
    foreach(1, n, i){
        if(arr[i] > n) root[i] = root[i-1];
        else root[i] = update(arr[i], i, 0, n, root[i-1]);
    }
    while(m--){
        int l, r;
        cin >> l >> r;
        cout << query(l, 0, n, root[r]) << '\n';
    }
}