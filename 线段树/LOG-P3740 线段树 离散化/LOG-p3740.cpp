#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int M = 1010;
int num[2*M], disNum[4*M], lazy[16*M];
bool vis[M];
int pos;

void push_down(int p){
    if(lazy[p]){
        lazy[p << 1] = lazy[p << 1 | 1] = lazy[p];
        lazy[p] = 0;
    }
}

void setVal(int L, int R, int val, int l, int r, int p){
    if(L <= l && r <= R){
        lazy[p] = val;
        return;
    }
    push_down(p);
    int mid = (l + r) >> 1;
    if(L <= mid) setVal(L, R, val, l, mid, p << 1);
    if(R > mid) setVal(L, R, val, mid+1, r, p << 1 | 1);
}

int query(int L, int R, int l, int r, int p){
    if(l == r){
        if(lazy[p] && !vis[lazy[p]]){
            return vis[lazy[p]] = 1;
        }
        else return 0;
    }
    push_down(p);
    int mid = (l + r) >> 1;
    int ans = 0;
    if(L <= mid){
        ans += query(L, R, l, mid, p << 1);
    }
    if(R > mid){
        ans += query(L, R, mid+1, r, p << 1 | 1);
    }
    return ans;
}

int Rank(int x){
    return lower_bound(disNum+1, disNum+pos+1, num[x]) - disNum;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;
    foreach(1, m, i){
        int a, b;
        cin >> a >> b;
        disNum[i] = num[i] = a, disNum[i+m] = num[i+m] = b;
    }
    int sz = 2*m+1;
    disNum[2*m+1] = num[0] = n;
    sort(disNum+1, disNum+sz+1);
    foreach(1, 2*m, i){
        if(disNum[i] + 1 < disNum[i+1]){
            disNum[++sz] = disNum[i] + 1;
        }
    }
    sort(disNum+1, disNum+sz+1);
    pos = unique(disNum+1, disNum+sz+1) - disNum - 1;
    foreach(1, m, i){
        int a = Rank(i), b = Rank(i+m);
        setVal(a, b, i, 1, pos, 1);
    }
    cout << query(1, Rank(0), 1, pos, 1);
}