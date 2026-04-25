#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 2010;
int tr[4*N], lazy[4*N] , a[N], b[N], h[N];

void push_up(int p){
    tr[p] = max(tr[p << 1], tr[p << 1 | 1]);
}

void update(int p, int v){
    tr[p] = v;
    lazy[p] = v;
}

void push_down(int p){
    if(lazy[p]){
        update(p << 1, lazy[p]);
        update(p << 1 | 1, lazy[p]);
        lazy[p] = 0;
    }
}

void build(int l, int r, int p){
    if(l == r){
        tr[p] = 0;
        return;
    }

    int mid = (l + r) >> 1;
    build(l, mid, p << 1);
    build(mid+1, r, p << 1 | 1);
    push_up(p);

    lazy[p] = 0;
}

void setVal(int L, int R, int v, int l, int r, int p){
    if(L <= l && r <= R){
        update(p, v);
        return;
    }

    int mid = (l + r) >> 1;
    push_down(p);
    if(L <= mid){
        setVal(L, R, v, l, mid, p << 1);
    }
    if(R > mid){
        setVal(L, R, v, mid+1, r, p << 1 | 1);
    }
    push_up(p);
}

int query(int L, int R, int l, int r, int p){
    if(L <= l && r <= R){
        return tr[p];
    }

    int mid = (l + r) >> 1;
    push_down(p);
    int ans = 0;
    if(L <= mid){
        ans = max(ans, query(L, R, l, mid, p << 1));
    }
    if(R > mid){
        ans = max(ans, query(L, R, mid+1, r, p << 1 | 1));
    }
    return ans;
}

class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        int n = positions.size();
        vector<int> ans;
        foreach(1, n, i){
            auto position = positions[i-1];
            a[i] = position[0], a[i+n] = position[0]+position[1]-1;
            h[i] = position[1];
        }
        foreach(1, 2*n, i){
            b[i] = a[i];
        }
        sort(b+1, b+2*n+1);
        int m = unique(b+1, b+2*n+1) - (b+1);
        build(1, m, 1);
        foreach(1, n, i){
            int l = lower_bound(b+1, b+m+1, a[i]) - b, r = lower_bound(b+1, b+m+1, a[i+n]) - b;
            //int L = b[l], R = b[r];
            int maxh = query(l, r, 1, m, 1);
            setVal(l, r, maxh+h[i], 1, m, 1);
            ans.push_back(query(1, m, 1, m, 1));
        }
        return ans;
    }
};