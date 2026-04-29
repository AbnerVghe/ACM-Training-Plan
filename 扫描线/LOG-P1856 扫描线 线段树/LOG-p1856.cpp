#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 3e4+10, OFFSET = 1e4+1;
int cover[N << 2], len[N << 2], cnt[N << 2];
struct Line{
    int x, y1, y2, val;
}line[N], line2[N];

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
    len[p] = r-l+1;
    cover[p] = cnt[p] = 0;
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

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n;
    cin >> n;
    foreach(1, n, i){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1 += OFFSET, x2 += OFFSET, y1 += OFFSET, y2 += OFFSET;
        line[i] = {x1, y1, y2, 1};
        line[i+n] = {x2, y1, y2, -1};
        line2[i] = {y1, x1, x2, 1};
        line2[i+n] = {y2, x1, x2, -1};
    }
    n <<= 1;
    sort(line+1, line+n+1, cmp);
    sort(line2+1, line2+n+1, cmp);
    //数据量小，可以不做离散化
    //x，y扫两次
    build(1, 1e4+OFFSET, 1);
    int ans1 = 0;
    for(int i = 1, pre = 0; i <= n; i++){
        add(line[i].y1, line[i].y2-1, line[i].val, 1, 1e4+OFFSET, 1);
        ans1 += fabs(cover[1] - pre);
        pre = cover[1];
    }
    build(1, 1e4+OFFSET, 1);
    int ans2 = 0;
    for(int i = 1, pre = 0; i <= n; i++){
        add(line2[i].y1, line2[i].y2-1, line2[i].val, 1, 1e4+OFFSET, 1);
        ans1 += fabs(cover[1] - pre);
        pre = cover[1];
    }
    cout << ans1+ans2 << '\n';
}