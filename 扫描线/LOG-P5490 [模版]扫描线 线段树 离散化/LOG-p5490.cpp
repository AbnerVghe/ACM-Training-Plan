#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 3e5+7;//?
int len[N << 2], cover[N << 2], cnt[N << 2];
int ysort[N];

struct Line{
    int x, y1, y2, val;
}line[N];

int pos;

bool cmp(Line A, Line B){
    return A.x < B.x;
}

void push_up(int p){
    if(cnt[p]) cover[p] = len[p];
    else cover[p] = cover[p << 1] + cover[p << 1 | 1];
}

void build(int l, int r, int p){
    if(l < r){
        int mid = (l + r) >> 1;
        build(l, mid, p << 1);
        build(mid+1, r, p << 1 | 1);
    }
    len[p] = ysort[r+1] - ysort[l];
    cnt[p] = cover[p] = 0;
}

void add(int L, int R, int v, int l, int r, int p){
    if(L <= l && r <= R){
        cnt[p] += v;
    }
    else{
        int mid = (l + r) >> 1;
        if(L <= mid) add(L, R, v, l, mid, p << 1);
        if(R > mid) add(L, R, v, mid+1, r, p << 1 | 1);
    }
    push_up(p);
}

int Rank(int val){
    return lower_bound(ysort+1, ysort+pos+1, val) - ysort;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n;
    cin >> n;
    foreach(1, n, i){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        ysort[i] = y1, ysort[i+n] = y2;
        line[i].x = x1, line[i].y1 = y1, line[i].y2 = y2, line[i].val = 1;
        line[i+n].x = x2, line[i+n].y1 = y1, line[i+n].y2 = y2, line[i+n].val = -1;
    }
    sort(line+1, line+2*n+1, cmp);
    sort(ysort+1, ysort+2*n+1);
    pos = unique(ysort+1, ysort+2*n+1) - (ysort+1);
    ysort[pos+1] = ysort[pos];//防止build时越界
    build(1, pos, 1);
    int ans = 0;
    for(int i = 1, pre = 0; i <= 2*n; i++){
        ans += (line[i].x - pre) * cover[1];
        pre = line[i].x;
        add(Rank(line[i].y1), Rank(line[i].y2)-1, line[i].val, 1, pos, 1);
    }
    cout << ans;
}