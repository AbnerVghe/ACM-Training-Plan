#include<bits/stdc++.h>
#define int long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 1e5+7;
int len[N], son[N], fid[N], gid[N], cnt, fa[N];
int f[N];//f[x][i] x子树中距离x为i的节点个数
int g[N << 1];//g[x][i] x子树中，假设有a,b两个点，a和b与其lca等距且距离等于x到lca加i的点对个数
vector<int> p[N];
int ans = 0;

void setf(int x, int i, int v){
    f[fid[x]+i] = v;
}

int getf(int x, int i){
    return f[fid[x]+i];
}

void setg(int x, int i, int v){
    g[gid[x]+i] = v;
}

int getg(int x, int i){
    return g[gid[x]+i];
}

//gid的赋予：
//由于g[父][i]依赖g[子][i+1]
//因此，设置gid规则：长链尾节点的开始位置=长链头的dfn*2， 长链从底到顶的节点，开始位置依次+1

void dfs1(int x, int f){
    fa[x] = f;
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
    fid[x] = ++cnt;
    if(!son[x]){//长链尾节点
        gid[x] = fid[t] * 2;
        return;
    }
    dfs2(son[x], t);
    for(auto v: p[x]){
        if(v == fa[x] || v == son[x]) continue;
        dfs2(v, v);
    }
    gid[x] = gid[son[x]] + 1;
}

void dfs3(int x){//获取答案
    setf(x, 0, 1);//距离x点为0的点就是它自己
    if(!son[x]) return;//没儿子不会产生点对的答案贡献
    dfs3(son[x]);
    for(auto v: p[x]){
        if(v == son[x] || v == fa[x]) continue;
        dfs3(v);
    }
    for(auto v: p[x]){
        if(v == son[x] || v == fa[x]) continue;
        //情况2：x树上选三个点，没有选x，但是跨过了x进行选点
        foreach(0, len[v], i){
            //分支1：之前遍历的子树里选两个点，当前子树里选一个点
            if(i < len[x] && i - 1 >= 0){//确保有点和不越界
                ans += getg(x, i) * getf(v, i-1);
            }
            //分支2：（反过来
            if(i > 0 && i + 1 < len[v]){
                ans += getf(x, i) * getg(v, i+1);
            }
        }
        foreach(0, len[v], i){//g的转移
            if(i + 1 < len[v]){
                setg(x, i, getg(x, i) + getg(v, i+1));
            }
            if(i - 1 >= 0){
                setg(x, i, getg(x, i) + getf(x, i)*getf(v, i-1));
            }
        }
        foreach(1, len[v], i){//f的转移
            setf(x, i, getf(x, i) + getf(v, i-1));
        }
    }
    //情况1：在x的子树中，x自己被选中
    ans += getg(x, 0);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n;
    cin >> n;
    foreach(1, n-1, i){
        int a, b;
        cin >> a >> b;
        p[a].push_back(b);
        p[b].push_back(a);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    dfs3(1);
    cout << ans;
}