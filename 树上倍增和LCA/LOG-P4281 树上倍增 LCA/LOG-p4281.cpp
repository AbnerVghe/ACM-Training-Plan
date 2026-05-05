#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 5e5+7, LMT = 20;
int st[N][LMT], dep[N];
vector<int> p[N];
int n, power;

int log2(int n){
    int ans = 0;
    while((1<<ans) <= (n>>1)){
        ans++;
    }
    return ans;
}

void dfs(int x, int fa){
    if(x == 1) dep[x] = 1;
    else dep[x] = dep[fa]+1;
    st[x][0] = fa;
    for(int j = 1; (1<<j) <= dep[x]; j++){
        st[x][j] = st[st[x][j-1]][j-1];
    }
    for(auto v: p[x]){
        if(v == fa) continue;
        dfs(v, x);
    }
}

void build(){
    power = log2(n);
    dfs(1, 1);
}

int lca(int x, int y){
    if(dep[x] < dep[y]) swap(x, y);
    int t = dep[x]-dep[y];
    foreach(0, power, j){
        if((t>>j)&1) x = st[x][j];
    }
    if(x == y) return x;
    foreach_sub(power, 0, j){
        if(st[x][j] != st[y][j]){
            x = st[x][j], y = st[y][j];
        }
    }
    return st[x][0];
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int m;
    cin >> n >> m;
    foreach(1, n-1, i){
        int a, b;
        cin >> a >> b;
        p[a].push_back(b);
        p[b].push_back(a);
    }
    build();
    foreach(1, m, i){
        int a, b, c;
        cin >> a >> b >> c;
        int x = lca(a,b), y = lca(b,c), z = lca(a,c);
        int disa = dep[a]-1, disb = dep[b]-1, disc = dep[c]-1;
        int ans;
        if(x == y && y == z){
            int disx = dep[x]-1;
            ans = disa + disb + disc - 3*disx;
        }
        else{
            if(x == z){
                swap(y, z);
            }
            else if(y == z){
                swap(x, z);
            }
            if(dep[x] < dep[z]) swap(x, z);
            int disx = dep[x]-1, disz = dep[z]-1;
            ans = disa+disb+disc - (disx+2*disz);
        }
        cout << x << ' ' << ans << '\n';
    }
}