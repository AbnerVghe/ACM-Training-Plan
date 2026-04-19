#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 5e6+7;
bool noPrime[N];
int prime[N/2 + 1];

//关键优化：相对于埃氏筛，欧拉筛使得每个合数只被自己最小的质因数筛掉，减少了重复筛除的情况
//因而复杂度O(n)

class Solution {
public:
    int countPrimes(int n) {
        n--;
        noPrime[0] = noPrime[1] = 1;
        foreach(2, n, i) noPrime[i] = 0;
        int cnt = 0;
        foreach(2, n, i){
            if(!noPrime[i]){
                prime[cnt++] = i;
            }
            foreach(0, cnt-1, j){//j:质数数组的下标
                if(i * prime[j] > n){//越界，无收集必要
                    break;
                }
                noPrime[i * prime[j]] = 1;//以j对应质数的名义去筛
                if(i % prime[j] == 0){//再往后筛就名义错误了
                    break;
                }
            } 
        } 
        return cnt;
    }
};