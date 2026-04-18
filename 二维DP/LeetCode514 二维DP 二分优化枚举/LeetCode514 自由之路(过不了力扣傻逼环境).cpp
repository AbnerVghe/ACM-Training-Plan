#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 110;
int n, m;
int dp[N][N];
vector<int> p[30][2];//0:+ 1:-
int Ring[N], Key[N];

int f(int i, int j){
    if(j == m+1) return 0;
    if(dp[i][j] != -1) return dp[i][j];

    int ans;
    if(Ring[i] == Key[j]) ans = f(i, j+1) + 1;
    else{
        int aim = Key[j] - 'a';
        auto jump1p = upper_bound(p[aim][0].begin(), p[aim][0].end(), i);
        int jump1;
        if(jump1p == p[aim][0].end()) jump1 = p[aim][0][0];
        else jump1 = *jump1p;
        int dist1 = (jump1 > i) ? (jump1 - i) : (n - i + jump1);

        auto jump2p = upper_bound(p[aim][1].begin(), p[aim][1].end(), -i);
        int jump2;
        if(jump2p == p[aim][1].end()) jump2 = -p[aim][1][0];
        else jump2 = -*jump2p;
        int dist2 = (i > jump2) ? (i - jump2) : (i + n - jump2);

        ans = min(dist1+1+f(jump1, j+1), dist2+1+f(jump2, j+1));
    }
    dp[i][j] = ans;
    return ans;
}

class Solution {
public:
    int findRotateSteps(string ring, string key) {
        n = ring.size(), m = key.size();
        foreach(1, n, i){
            Ring[i] = ring[i-1];
            Key[i] = key[i-1];
        }

        foreach(0, n+1, i) foreach(0, m+1, j) dp[i][j] = -1;
        foreach('a', 'z', i) foreach(0, 1, j) p[i-'a'][j].clear();
        
        foreach(1, n, i){
            int lt = Ring[i] - 'a';
            p[lt][0].push_back(i);
            p[lt][1].push_back(-i);
        }
        foreach('a', 'z', i){
            foreach(0, 1, j){
                sort(p[i-'a'][j].begin(), p[i-'a'][j].end());
            }
        }

        return f(1, 1);
    }
};