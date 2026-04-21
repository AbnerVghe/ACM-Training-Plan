#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int MOD = 1e9+7, maxS = 1510;
int tree[maxS][10], fail[maxS];
bool alert[maxS];
int cnt;
int box[maxS];

const int N = 1210;
int dp[N][maxS][2][2];
string num;
int n;

void ins(string s){
    int cur = 0;
    for(auto c: s){
        int path = c - '0';
        if(!tree[cur][path]) tree[cur][path] = ++cnt;
        cur = tree[cur][path];
    }
    alert[cur] = 1;
}

void setFail(){
    int l = 0, r = 0;
    foreach(0, 9, i){
        if(tree[0][i]) box[r++] = tree[0][i];
    }
    while(l < r){
        int u = box[l++];
        foreach(0, 9, i){
            if(tree[u][i]){
                fail[tree[u][i]] = tree[fail[u]][i];
                box[r++] = tree[u][i];
            }
            else{
                tree[u][i] = tree[fail[u]][i];
            }
            //命中标记前移
            alert[u] |= alert[fail[u]];
        }
    }
}

void build(){
    foreach(0, n, i) foreach(0, cnt, j) foreach(0, 1, k1) foreach(0, 1, k2){
        dp[i][j][k1][k2] = -1;
    }
}

int f(int i, int j, bool free, bool pre){
    if(alert[j]) return 0;
    if(i == n) return pre;

    if(dp[i][j][free][pre] != -1) return dp[i][j][free][pre];
    int ans = 0;
    int now = num[i] - '0';
    if(!free){//不能随便选
        if(!pre) ans = (ans + f(i+1, j, 1, 0))%MOD;
        else if(now > 0) ans = (ans + f(i+1, tree[j][0], 1, 1))%MOD;
        foreach(1, now-1, pick){
            ans = (ans + f(i+1, tree[j][pick], 1, 1))%MOD;
        }
        ans = (ans + f(i+1, tree[j][now], 0, 1))%MOD;
    }
    else{
        if(!pre) ans = (ans + f(i+1, j, 1, 0))%MOD;
        else ans = (ans + f(i+1, tree[j][0], 1, 1))%MOD;
        foreach(1, 9, pick){
            ans = (ans + f(i+1, tree[j][pick], 1, 1))%MOD;
        }
    }
    dp[i][j][free][pre] = ans;
    return ans;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> num;
    n = num.length();
    int m;
    cin >> m;
    foreach(1, m, i){
        string tmp;
        cin >> tmp;
        ins(tmp);
    }
    setFail();
    build();
    cout << f(0, 0, 0, 0);
}