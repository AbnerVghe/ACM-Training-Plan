#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 1e5+7;
//sum:不是真实的累加和，而是在之前的任务中，不考虑被上方截断的任务，只考虑来到当前节点或者更下的任务的情形下，累加和变为多少
int arr[N], sum[N << 2], addTag[N << 2];

void build(int l, int r, int p){
    if(l == r){
        sum[p] = arr[l];
    }
    else{
        int mid = (l + r) >> 1;
        build(l, mid, p << 1);
        build(mid+1, r, p << 1 | 1);
        sum[p] = sum[p << 1] + sum[p << 1 | 1];
    }
    addTag[p] = 0;
}

void add(int L, int R, int v, int l, int r, int p){
    int a = max(L, l), b = min(R, r);//实际影响的范围
    sum[p] += v * (b-a+1);
    if(L <= l && r <= R){//全包，更新节点标记
        addTag[p] += v;
    }
    else{
        int mid = (l + r) >> 1;
        if(L <= mid) add(L, R, v, l, mid, p << 1);
        if(R > mid) add(L, R, v, mid+1, r, p << 1 | 1);
    }
}

int query(int L, int R, int addHistory, int l, int r, int p){
    if(L <= l && r <= R){
        return sum[p] + addHistory * (r-l+1);
    }
    int mid = (l + r) >> 1;
    int ans = 0;
    //查询时把之前获取过的标记全部带下去
    if(L <= mid) ans += query(L, R, addHistory+addTag[p], l, mid, p<< 1);
    if(R > mid) ans += query(L, R, addHistory+addTag[p], mid+1, r, p << 1 | 1);
    return ans;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n, m;
    cin >> n >> m;
    foreach(1, n, i){
        cin >> arr[i];
    }
    build(1, n, 1);
    while(m--){
        int opt, x, y, k;
        cin >> opt >> x >> y;
        if(opt == 1){
            cin >> k;
            add(x, y, k, 1, n, 1);
        }
        else{
            cout << query(x, y, 0, 1, n, 1) << '\n';
        }
    }
}