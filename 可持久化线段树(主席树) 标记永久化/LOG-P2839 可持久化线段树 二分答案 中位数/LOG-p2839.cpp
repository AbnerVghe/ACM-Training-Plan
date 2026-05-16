#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 2e4+7;
const int T = N * 30;
int root[N], arr[N], maxpre[T], maxsuf[T], sum[T], Left[T], Right[T], cnt;
int n;

void push_up(int p){
    int lp = Left[p], rp = Right[p];
    sum[p] = sum[lp] + sum[rp];
    maxpre[p] = max(maxpre[lp], sum[lp]+maxpre[rp]);
    maxsuf[p] = max(maxsuf[rp], maxsuf[lp]+sum[rp]);
}

int build(int l, int r){
    int rt = ++cnt;
    if(l == r){
        maxpre[rt] = maxsuf[rt] = sum[rt] = 1; 
    }
    else{
        int mid = (l + r) >> 1;
        Left[rt] = build(l, mid);
        Right[rt] = build(mid+1, r);
        push_up(rt);
    }
    return rt;
}

int clone(int p){
    int rt = ++cnt;
    Left[rt] = Left[p];
    Right[rt] = Right[p];
    sum[rt] = sum[p];
    maxpre[rt] = maxpre[p];
    maxsuf[rt] = maxsuf[p];
    return rt;
}

int insert(int x, int v, int l, int r, int p){
    int rt = clone(p);
    if(l == r){
        sum[rt] = maxpre[rt] = maxsuf[rt] = v;
    }
    else{
        int mid = (l + r) >> 1;
        if(x <= mid) Left[rt] = insert(x, v, l, mid, Left[rt]);
        else Right[rt] = insert(x, v, mid+1, r, Right[rt]);
        push_up(rt);
    }
    return rt;
}

struct Info{
    int sum, maxpre, maxsuf;
};

Info mergeInfo(Info l, Info r){
    Info ans;
    ans.sum = l.sum + r.sum;
    ans.maxpre = max(l.maxpre, l.sum+r.maxpre);
    ans.maxsuf = max(r.maxsuf, l.maxsuf+r.sum);
    return ans;
}

Info query(int L, int R, int l, int r, int p){
    if(L <= l && r <= R){
        return {sum[p], maxpre[p], maxsuf[p]};
    }
    int mid = (l + r) >> 1;
    Info ans = {0, -INF, -INF};
    if(L <= mid) ans = mergeInfo(ans, query(L, R, l, mid, Left[p]));
    if(R > mid) ans = mergeInfo(ans, query(L, R, mid+1, r, Right[p]));
    return ans;
}

struct Sorted{
    int val, pos;
}sorted[N];

bool cmp(Sorted A, Sorted B){
    return A.val < B.val;
}

bool check(int a, int b, int c, int d, int ver){
    int suf = query(a, b, 1, n, root[ver]).maxsuf;
    int pre = query(c, d, 1, n, root[ver]).maxpre;
    int ans = suf + pre;
    if(b+1 <= c-1) ans += query(b+1, c-1, 1, n, root[ver]).sum;
    return ans >= 0;
}

int queryAns(int a, int b, int c, int d){
    int L = 1, R = n;
    while(L < R){
        int mid = (L + R + 1) / 2;
        if(check(a, b, c, d, mid)){
            L = mid;
        }
        else R = mid - 1;
    }
    return sorted[L].val;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    foreach(1, n, i){
        int val;
        cin >> val;
        arr[i] = val;
        sorted[i] = {val, i};
    }
    sort(sorted+1, sorted+n+1, cmp);
    root[1] = build(1, n);
    foreach(2, n, i){
        root[i] = insert(sorted[i-1].pos, -1, 1, n, root[i-1]);
    }
    int q, lastAns = 0;
    cin >> q;
    int que[4];
    while(q--){
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        que[0] = (a + lastAns) % n;
        que[1] = (b + lastAns) % n;
        que[2] = (c + lastAns) % n;
        que[3] = (d + lastAns) % n;
        sort(que, que+4);
        a = que[0] + 1;
        b = que[1] + 1;
        c = que[2] + 1;
        d = que[3] + 1;
        int x = queryAns(a, b, c, d);
        cout << x << '\n';
        lastAns = x;
    }
}