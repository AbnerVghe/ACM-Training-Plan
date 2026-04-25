#include<bits/stdc++.h>
#define double long double
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define eqs 1e-8
using namespace std;

const int N = 1e5+7;
double sum[4*N], powSum[4*N], a[N], lazy[4*N];

void push_up(int p){
    sum[p] = sum[p << 1] + sum[p << 1 | 1];
    powSum[p] = powSum[p << 1] + powSum[p << 1 | 1];
}

void update(int p, double v, int n){
    powSum[p] += 2 * sum[p] * v + n * v * v;
    sum[p] += v * n;
    lazy[p] += v;
}

void push_down(int p, int ln, int rn){
    if(lazy[p] != 0){
        update(p << 1, lazy[p], ln);
        update(p << 1 | 1, lazy[p], rn);
        lazy[p] = 0;
    }
}

void build(int l, int r, int p){
    if(l == r){
        sum[p] = a[l];
        powSum[p] = a[l] * a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, p << 1);
    build(mid+1, r, p << 1 | 1);
    push_up(p);
    lazy[p] = 0; 
}

void addVal(int L, int R, double v, int l, int r, int p){
    if(L <= l && r <= R){
        update(p, v, r-l+1);
        return;
    }
    int mid = (l + r) >> 1;
    push_down(p, mid-l+1, r-mid);
    if(L <= mid){
        addVal(L, R, v, l, mid, p << 1);
    }
    if(R > mid){
        addVal(L, R, v, mid+1, r, p << 1 | 1);
    }
    push_up(p);
}

double queryAvr(int L, int R, int l, int r, int p){//实际上是求sum
    if(L <= l && r <= R){
        return sum[p];
    }
    int mid = (l + r) >> 1;
    push_down(p, mid-l+1, r-mid);
    double ans = 0;
    if(L <= mid) ans += queryAvr(L, R, l, mid, p << 1);
    if(R > mid) ans += queryAvr(L, R, mid+1, r, p << 1 | 1);
    return ans;
}

double queryPowSum(int L, int R, int l, int r, int p){
    if(L <= l && r <= R){
        return powSum[p];
    }
    int mid = (l + r) >> 1;
    push_down(p, mid-l+1, r-mid);
    double ans = 0;
    if(L <= mid) ans += queryPowSum(L, R, l, mid, p << 1);
    if(R > mid) ans += queryPowSum(L, R, mid+1, r, p << 1 | 1);
    return ans;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);    

    int n, m;
    cin >> n >> m;
    foreach(1, n, i){
        cin >> a[i];
    }
    build(1, n, 1);
    cout << fixed << setprecision(4);
    while(m--){
        int opt, l, r;
        cin >> opt >> l >> r;
        if(opt == 1){
            double k;
            cin >> k;
            addVal(l, r, k, 1, n, 1);
        }
        else if(opt == 2){
            cout << queryAvr(l, r, 1, n, 1) / (r-l+1) << '\n';
        }
        else{
            double avr = queryAvr(l, r, 1, n, 1) / (r-l+1), powS = queryPowSum(l, r, 1, n, 1);
            int len = r - l + 1;
            double var = powS / len - avr * avr;
            cout << var << '\n';
        }
    }
}