#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 1e6+7;
int maxVal[4*N], semVal[4*N], cnt[4*N];//严格次大值，最大值出现次数
ll sum[4*N];
int a[N];

/*
势能分析：
每次给最大值和父亲最大值不同的节点打上“标签”，可以发现，当一个节点所在子树均无标签时
其所在子树必然不再存在严格次大值（从而实现剪枝，另一方面说就是势能减小）
这种减小来自于push_up时的标签回收
回收所有标签的次数的极端情形是O(n)级别
而单次摘取极端复杂度为树深，即约O(logn)级别
从而实现势能最大为O(nlogn)级别，均摊操作复杂度O(logn)
*/

void push_up(int p){
    int l = p << 1, r = p << 1 | 1;
    sum[p] = sum[l] + sum[r];
    maxVal[p] = max(maxVal[l], maxVal[r]);
    if(maxVal[l] > maxVal[r]){
        cnt[p] = cnt[l];
        semVal[p] = max(semVal[l], maxVal[r]);
    }
    else if(maxVal[l] < maxVal[r]){
        cnt[p] = cnt[r];
        semVal[p] = max(maxVal[l], semVal[r]);
    }
    else{
        cnt[p] = cnt[l] + cnt[r];
        semVal[p] = max(semVal[l], semVal[r]);
    }
}

//一定是没有颠覆掉次大值的懒更新信息下发
//即最大值被压成v，并且v > 严格次大值的情形下如何调整sum和maxVal
//此处，maxVal兼具最大值和懒标的功能
void update(int p, int v){
    if(v < maxVal[p]){
        sum[p] -= ((ll)maxVal[p] - v) * cnt[p];
        maxVal[p] = v;
    }
}

void push_down(int p){
    update(p << 1, maxVal[p]);
    update(p << 1 | 1, maxVal[p]);
}

void setMin(int L, int R, int v, int l, int r, int p){
    if(v >= maxVal[p]) return;//修改的值大于最大值
    if(L <= l && r <= R && v > semVal[p]) update(p, v);//全包 且介于次大值和最大值之间
    else{
        //1.没有全包
        //2.semVal >= v
        int mid = (l + r) >> 1;
        push_down(p);
        if(L <= mid) setMin(L, R, v, l, mid, p << 1);
        if(R > mid) setMin(L, R, v, mid+1, r, p << 1 | 1);
        push_up(p);
    }
}

void build(int l, int r, int p){
    if(l == r){
        sum[p] = maxVal[p] = a[l];
        cnt[p] = 1;
        semVal[p] = INT_MIN;
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, p << 1);
    build(mid+1, r, p << 1 | 1);
    push_up(p);
}

ll querySum(int L, int R, int l, int r, int p){
    if(L <= l && r <= R) return sum[p];
    int mid = (l + r) >> 1;
    push_down(p);
    ll ans = 0;
    if(L <= mid) ans += querySum(L, R, l, mid, p << 1);
    if(R > mid) ans += querySum(L, R, mid+1, r, p << 1 | 1);
    return ans;
}

int queryMax(int L, int R, int l, int r, int p){
    if(L <= l && r <= R) return maxVal[p];
    int mid = (l + r) >> 1;
    push_down(p);
    int maxV = INT_MIN;
    if(L <= mid) maxV = max(maxV, queryMax(L, R, l, mid, p << 1));
    if(R > mid) maxV = max(maxV, queryMax(L, R, mid+1, r, p << 1 | 1));
    return maxV;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int T;
    cin >> T;
    while(T--){
        int n, m;
        cin >> n >> m;
        foreach(1, n, i) cin >> a[i];
        build(1, n, 1);
        while(m--){
            int opt, x, y;
            cin >> opt >> x >> y;
            if(opt == 0){
                int t;
                cin >> t;
                setMin(x, y, t, 1, n, 1);
            }
            else if(opt == 1){
                cout << queryMax(x, y, 1, n, 1) << '\n';
            }
            else{
                cout << querySum(x, y, 1, n, 1) << '\n';
            }
        }
    }
}