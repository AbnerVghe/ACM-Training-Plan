#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 3e6+7;
int tree[N][2];
int cnt, lmt;

void ins(int num){
    int cur = 1;
    foreach_sub(lmt, 0, i){
        int path = (num >> i) & 1;
        if(!tree[cur][path]) tree[cur][path] = ++cnt;
        cur = tree[cur][path];
    }
}

void build(vector<int>& nums){
    cnt = 1, lmt = 0;
    int maxn = 0;
    for(auto num: nums){
        maxn = max(maxn, num);
    }
    foreach_sub(30, 0, i){
        if((maxn >> i)&1){
            lmt = i;
            break;
        }
    }
    for(auto num: nums){
        ins(num);
    }
}

int maxXor(int num){
    int cur = 1, ans = 0;
    foreach_sub(lmt, 0, i){
        int status = (num >> i) & 1;
        int want = status ^ 1;
        if(!tree[cur][want]){
            want ^= 1;
        }
        cur = tree[cur][want];
        ans |= (status ^ want) << i;
    }
    return ans;
}

void clr(){
    foreach(1, cnt, i) foreach(0, 1, j) tree[i][j] = 0;
}

class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        build(nums);
        int ans = 0;
        for(auto num: nums){
            ans = max(ans, maxXor(num));
        }
        clr();
        return ans;
    }
};