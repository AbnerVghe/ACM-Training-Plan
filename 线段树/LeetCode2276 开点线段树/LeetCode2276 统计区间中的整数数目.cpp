#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 7e6+7;
int Left[N], Right[N], sum[N];
int cnt = 1;

class CountIntervals {
public:
    int n = 1e9;

    CountIntervals() {
        foreach(0, 7e6, i){//傻逼力扣
            Left[i] = Right[i] = sum[i] = 0;
            cnt = 1;
        }
    }
    
    void push_up(int p, int l, int r){
        sum[p] = sum[l] + sum[r];
    }

    void change(int L, int R, int l, int r, int p){
        if(sum[p] == r-l+1) return;
        
        if(L <= l && r <= R){
            sum[p] = r-l+1;
            return;
        }

        int mid = (l + r) >> 1;
        if(L <= mid){
            if(!Left[p]) Left[p] = ++cnt;
            change(L, R, l, mid, Left[p]);
        }
        if(R > mid){
            if(!Right[p]) Right[p] = ++cnt;
            change(L, R, mid+1, r, Right[p]);
        }
        push_up(p, Left[p], Right[p]);
    }

    void add(int left, int right) {
        change(left, right, 1, n, 1);
    }
    
    int count() {
        return sum[1];
    }
};

/**
 * Your CountIntervals object will be instantiated and called as such:
 * CountIntervals* obj = new CountIntervals();
 * obj->add(left,right);
 * int param_2 = obj->count();
 */