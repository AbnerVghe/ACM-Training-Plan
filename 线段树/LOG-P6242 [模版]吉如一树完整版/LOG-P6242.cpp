#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 5e5+7;
int sum[N << 2];
int maxVal[N << 2];//最大值，仅仅是查询标记
int semVal[N << 2];//严格次大值
int cnt[N << 2];//最大值个数
int maxAdd[N << 2];//最大值的懒标记
int otherAdd[N << 2];//其他值的懒标记
int maxHistory[N << 2];//历史最大值
int maxAddTop[N << 2];//最大值达到过的最大提升幅度
int otherAddTop[N << 2];//其他值达到过的最大提升幅度
int a[N];


void push_up(int p){
    int l = p << 1, r = p << 1 | 1;
    maxHistory[p] = max(maxHistory[l], maxHistory[r]);
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

//maxAddv 最大值增加多少
//maxUpv 最大值达到过的最大提升幅度
void update(int p, int n, int maxAddv, int otherAddv, int maxUpv, int otherUpv){
    maxHistory[p] = max(maxHistory[p], maxVal[p]+maxUpv);
    maxAddTop[p] = max(maxAddTop[p], maxAdd[p]+maxUpv);
    otherAddTop[p] = max(otherAddTop[p], otherAdd[p]+otherUpv);
    sum[p] += maxAddv * cnt[p] + otherAddv * (n-cnt[p]);
    maxVal[p] += maxAddv;
    if(semVal[p] != INT_MIN) semVal[p] += otherAddv;
    maxAdd[p] += maxAddv;
    otherAdd[p] += otherAddv;
}

void push_down(int p, int ln, int rn){
    int l = p << 1, r = p << 1 | 1;
    int tmp = max(maxVal[l], maxVal[r]);//tmp 相当于全局最大值
    if(maxVal[l] == tmp){
        update(l, ln, maxAdd[p], otherAdd[p], maxAddTop[p], otherAddTop[p]);
    }
    else update(l, ln, otherAdd[p], otherAdd[p], otherAddTop[p], otherAddTop[p]);
    if(maxVal[r] == tmp){
        update(r, rn, maxAdd[p], otherAdd[p], maxAddTop[p], otherAddTop[p]);
    }
    else update(r, rn, otherAdd[p], otherAdd[p], otherAddTop[p], otherAddTop[p]);
    maxAdd[p] = otherAdd[p] = maxAddTop[p] = otherAddTop[p] = 0;
}

void build(int l, int r, int p){
    maxAdd[p] = otherAdd[p] = maxAddTop[p] = otherAddTop[p] = 0;
    if(l == r){
        maxVal[p] = sum[p] = maxHistory[p] = a[l];
        cnt[p] = 1;
        semVal[p] = INT_MIN;
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, p << 1);
    build(mid+1, r, p << 1 | 1);
    push_up(p);
}

void add(int L, int R, int v, int l, int r, int p){
    if(L <= l && r <= R){
        update(p, r-l+1, v, v, v, v);
        return;
    }
    int mid = (l + r) >> 1;
    push_down(p, mid-l+1, r-mid);
    if(L <= mid) add(L, R, v, l, mid, p << 1);
    if(R > mid) add(L, R, v, mid+1, r, p << 1 | 1);
    push_up(p);
}

void setMin(int L, int R, int v, int l, int r, int p){
    if(v >= maxVal[p]) return;
    if(L <= l && r <= R && v > semVal[p]){
        update(p, r-l+1, v-maxVal[p], 0, v-maxVal[p], 0);
        return;
    }
    int mid = (l + r) >> 1;
    push_down(p, mid-l+1, r-mid);
    if(L <= mid) setMin(L, R, v, l, mid, p << 1);
    if(R > mid) setMin(L, R, v, mid+1, r, p << 1 | 1);
    push_up(p);
}

int querySum(int L, int R, int l, int r, int p){
    if(L <= l && r <= R) return sum[p];
    int mid = (l + r) >> 1;
    push_down(p, mid-l+1, r-mid);
    int ans = 0;
    if(L <= mid) ans += querySum(L, R, l, mid, p << 1);
    if(R > mid) ans += querySum(L, R, mid+1, r, p << 1 | 1);
    return ans;
}

int queryMax(int L, int R, int l, int r, int p){
    if(L <= l && r <= R) return maxVal[p];
    int mid = (l + r) >> 1;
    push_down(p, mid-l+1, r-mid);
    int ans = INT_MIN;
    if(L <= mid) ans = max(ans, queryMax(L, R, l, mid, p << 1));
    if(R > mid) ans = max(ans, queryMax(L, R, mid+1, r, p << 1 | 1));
    return ans;
}

int queryHistoryMax(int L, int R, int l, int r, int p){
    if(L <= l && r <= R) return maxHistory[p];
    int mid = (l + r) >> 1;
    push_down(p, mid-l+1, r-mid);
    int ans = INT_MIN;
    if(L <= mid) ans = max(ans, queryHistoryMax(L, R, l, mid, p << 1));
    if(R > mid) ans = max(ans, queryHistoryMax(L, R, mid+1, r, p << 1 | 1));
    return ans;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n, m;
    cin >> n >> m;
    foreach(1, n, i) cin >> a[i];
    build(1, n, 1);
    while(m--){
        int opt, l, r;
        cin >> opt >> l >> r;
        if(opt == 1){
            int k;
            cin >> k;
            add(l, r, k, 1, n, 1);
        }
        else if(opt == 2){
            int v;
            cin >> v;
            setMin(l, r, v, 1, n, 1);
        }
        else if(opt == 3){
            cout << querySum(l, r, 1, n, 1) << '\n';
        }
        else if(opt == 4){
            cout << queryMax(l, r, 1, n, 1) << '\n';
        }
        else{
            cout << queryHistoryMax(l, r, 1, n, 1) << '\n';
        }
    }
}