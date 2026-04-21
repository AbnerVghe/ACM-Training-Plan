#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int maxS = 310;
int tree[maxS][3], fail[maxS];
int cnt;
int ed[maxS], val[maxS];
int box[maxS];
const int K = 1e3+7;
int dp[K][maxS];

void ins(string s){
    int cur = 0;
    for(auto c: s){
        int path = c - 'A';
        if(!tree[cur][path]) tree[cur][path] = ++cnt;
        cur = tree[cur][path];
    }
    ed[cur]++;
}

void setFail(){
    int l = 0, r = 0;
    foreach(0, 2, i){
        if(tree[0][i]) box[r++] = tree[0][i];
    }
    while(l < r){
        int u = box[l++];
        foreach(0, 2, i){
            if(tree[u][i]){
                fail[tree[u][i]] = tree[fail[u]][i];
                box[r++] = tree[u][i];
            }
            else{
                tree[u][i] = tree[fail[u]][i];
            }
        }
    }
}

void calVal(int u){
    int ans = 0, cur = u;
    while(cur){
        ans += ed[cur];
        cur = fail[cur];
    }
    val[u] += ans;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, k;
    cin >> n >> k;
    foreach(1, n, i){
        string tmp;
        cin >> tmp;
        ins(tmp);
    }
    setFail();
    foreach(1, cnt, i) calVal(i);

    foreach(0, k, i) foreach(0, cnt, j) dp[i][j] = INT_MIN;
    dp[0][0] = 0;
    foreach(0, k-1, i){
        foreach(0, cnt, j){
            foreach(0, 2, path){
                int v = tree[j][path];
                dp[i+1][v] = max(dp[i+1][v], dp[i][j]+val[v]);
            }
        }
    }
    int ans = 0;
    foreach(0, cnt, i) ans = max(ans, dp[k][i]);
    cout << ans;
}