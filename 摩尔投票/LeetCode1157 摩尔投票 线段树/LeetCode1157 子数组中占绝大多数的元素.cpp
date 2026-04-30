#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 2e4+7;
int cand[N << 2], hp[N << 2];
int a[N];

struct Num{
    int val, id;
}nums[N];

struct Info{
    int can, cnt;
};

bool cmp(Num A, Num B){
    if(A.val == B.val) return A.id < B.id;
    else return A.val < B.val;
}

class MajorityChecker {
public:
    int n;

    int bs(int v, int i){
        int l = 1, r = n;
        int L, R;
        while(l < r){
            int mid = (l + r) >> 1;
            if(nums[mid].val < v){
                l = mid+1;
            }
            else r = mid;
        }
        L = l;
        l = 1, r = n;
        while(l < r){
            int mid = (l + r + 1) >> 1;
            if(nums[mid].val <= v){
                l = mid;
            }
            else r = mid-1;
        }
        int tmpR;
        tmpR = R = l;
        while(L < R){
            int mid = (L + R) >> 1;
            if(nums[mid].id < i){
                L = mid+1;
            }
            else R = mid;
        }
        return (nums[L].id < i) ? (tmpR+1) : L;
    }

    MajorityChecker(vector<int>& arr) {
        n = arr.size();
        foreach(1, n, i){
            nums[i] = {arr[i-1], i};
        }
        sort(nums+1, nums+n+1, cmp);
        foreach(1, n, i){
            a[i] = arr[i-1];
        }
        build(1, n, 1);
    }
    
    void push_up(int p){
        int lc = cand[p << 1], lh = hp[p << 1];
        int rc = cand[p << 1 | 1], rh = hp[p << 1 | 1];
        cand[p] = (lc == rc || lh >= rh) ? lc : rc;
        hp[p] = (lc == rc) ? (lh+rh) : abs(lh-rh);
    }

    void build(int l, int r, int p){
        if(l == r){
            cand[p] = a[l];
            hp[p] = 1;
            return;
        }
        int mid = (l + r) >> 1;
        build(l, mid, p << 1);
        build(mid+1, r, p << 1 | 1);
        push_up(p);
    }

    Info queryCnt(int L, int R, int l, int r, int p){
        if(L <= l && r <= R){
            return (Info){cand[p], hp[p]};
        }
        int mid = (l + r) >> 1;
        if(R <= mid) return queryCnt(L, R, l, mid, p << 1);
        if(L > mid) return queryCnt(L, R, mid+1, r, p << 1 | 1);
        Info infoL = queryCnt(L, R, l, mid, p << 1);
        Info infoR = queryCnt(L, R, mid+1, r, p << 1 | 1);
        int lc = infoL.can, lh = infoL.cnt;
        int rc = infoR.can, rh = infoR.cnt;
        int can = (lc == rc || lh >= rh) ? lc : rc;
        int cnt = (lc == rc) ? (lh+rh) : abs(lh-rh);
        return (Info){can, cnt};
    }

    int query(int left, int right, int threshold) {
        Info info = queryCnt(left+1, right+1, 1, n, 1);
        int num = info.can;
        int cnt = bs(num, right+2) - bs(num, left+1);
        return (cnt >= threshold) ? num : -1;
    }
};

/**
 * Your MajorityChecker object will be instantiated and called as such:
 * MajorityChecker* obj = new MajorityChecker(arr);
 * int param_1 = obj->query(left,right,threshold);
 */