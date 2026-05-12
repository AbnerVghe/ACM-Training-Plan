#include<bits/stdc++.h>
#define ll long long
#define ui unsigned int
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 5e5+7, L = 20;
int dep[N], len[N], st[N][25], son[N], top[N], dfn[N], cnt; 
vector<int> p[N];
int high[N], up[N], down[N];//high:对应数字最高位的1在第几位
int n, root;
ui s;

inline ui get(ui x){
    x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return s = x; 
}


void dfs1(int x, int f){
    st[x][0] = f;
    foreach(1, L, j){
        st[x][j] = st[st[x][j-1]][j-1];
    }
    dep[x] = dep[f] + 1;
    for(auto v: p[x]){
        if(v == f) continue;
        dfs1(v, x);
        if(!son[x] || len[son[x]] < len[v]){
            son[x] = v;
        }
    }
    len[x] = len[son[x]] + 1;
}

void dfs2(int x, int t){
    top[x] = t;
    dfn[x] = ++cnt;
    if(!son[x]) return;
    dfs2(son[x], t);
    for(auto v: p[x]){
        if(v == st[x][0] || v == son[x]) continue;
        dfs2(v, v);
    }
}

void setUp(int x, int i, int v){
    up[dfn[x] + i] = v;
}

int getUp(int x, int i){
    return up[dfn[x] + i];
}

void setDown(int x, int i, int v){
    down[dfn[x] + i] = v;
}

int getDown(int x, int i){
    return down[dfn[x] + i];
}

void prepare(){
    dfs1(root, root);
    dfs2(root, root);
    high[0] = -1;
    foreach(1, n, i){
        high[i] = high[i >> 1] + 1;
    }
    foreach(1, n, x){
        if(top[x] == x){
            for(int i = 0, a = x, b = x; i < len[x]; i++, a = st[a][0], b = son[b]){
                setUp(x, i, a);
                setDown(x, i, b); 
            }
        }
    }
}

int query(int x, int k){
    if(k == 0) return x;
    if(k == 1 << high[k]) return st[x][high[k]];
    x = st[x][high[k]];
    k -= 1 << high[k];
    k -= dep[x] - dep[top[x]];
    x = top[x];
    return (k >= 0) ? getUp(x, k) : getDown(x, -k);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int q;
    cin >> n >> q >> s;
    foreach(1, n, i){
        int f;
        cin >> f;
        if(f){
            p[f].push_back(i);
        }
        else root = i;
    }
    prepare();
    ll ans = 0;
    for(int i = 1, x, k, lastAns = 0; i <= q; i++){
        x = (get(s) ^ lastAns) % n + 1;
        k = (get(s) ^ lastAns) % dep[x];
        lastAns = query(x, k);
        ans ^= (ll) i * lastAns;
    }
    cout << ans;
}