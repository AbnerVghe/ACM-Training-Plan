#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 510;
int dp[N][N];
int f[N];

class Solution {
public:
    int minDistance(string word1, string word2) {
        //return minDistance2(word1, word2, 1, 1, 1);
        return minDistance3(word1, word2, 1, 1, 1);
    }

    int minDistance2(string word1, string word2, int a, int b, int c){
        int n = word1.length(), m = word2.length();
        foreach(0, n, i) dp[i][0] = i*b;
        foreach(1, m, j) dp[0][j] = j*a;
        foreach(1, n, i) foreach(1, m, j){
            if(word1[i-1] == word2[j-1]) dp[i][j] = dp[i-1][j-1];
            else{
                dp[i][j] = min(dp[i-1][j-1]+c, min(dp[i][j-1]+a, dp[i-1][j]+b));
            }
        }
        return dp[n][m];
    }

    int minDistance3(string word1, string word2, int a, int b, int c){
        int n = word1.length(), m = word2.length();
        foreach(0, m, i) f[i] = i*a;
        foreach(1, n, i){
            f[0] = i*b;
            int leftup = (i-1)*b;
            foreach(1, m, j){
                int tmp = f[j];
                if(word1[i-1] == word2[j-1]) f[j] = leftup;
                else{
                    f[j] = min(leftup+c, min(f[j-1]+a, f[j]+b));
                }
                leftup = tmp;
            }
        }
        return f[m];
    }
};

signed main(){
    Solution slu;
    string s1 = "intention", s2 = "execution";
    cout << slu.minDistance(s1, s2);
}
