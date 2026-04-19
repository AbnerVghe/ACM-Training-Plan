#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 2e4+7, M = 1e5+7;
int fa[N], sz[N];
int fac[M];
int n;

void init(){
    foreach(0, n-1, i){
        fa[i] = i;
        sz[i] = 1;
    }

    foreach(0, 1e5, i) fac[i] = -1;
}

int find(int x){
    if(fa[x] != x){
        fa[x] = find(fa[x]);
    }
    return fa[x];
}

void add(int x, int y){
    int fx = find(x), fy = find(y);
    if(fx != fy){
        fa[fx] = fy;
        sz[fy] += sz[fx];
    }
}

void change(int facNum, int i){
    if(fac[facNum] == -1) fac[facNum] = i;
    else add(i, fac[facNum]);
}

class Solution {
public:
    int largestComponentSize(vector<int>& nums) {
        n = nums.size();
        init();

        foreach(0, n-1, i){
            int num = nums[i];
            for(int j = 2; j * j <= num; j++){
                if(num % j == 0){
                    change(j, i);
                    while(num % j == 0) num /= j;
                }
            }
            if(num > 1) change(num, i);
        }

        int ans = 0;
        foreach(0, n-1, i) ans = max(ans, sz[i]);
        return ans;
    }
};