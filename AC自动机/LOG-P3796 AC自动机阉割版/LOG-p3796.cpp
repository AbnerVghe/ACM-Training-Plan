#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 160, maxS = 1e6 + 7;//maxS:字符串总字符上限
int tree[maxS][26], fail[maxS];//tree[][]:直通表
int cnt = 0;
int ed[N];//这个不是trie的ed，是每个目标串对应的终止节点编号
int box[maxS];//可用作队列/栈


//具体题目相关，本题：收集词频
int times[maxS];
int n;

//建反图用的链式前向星
int head[maxS], nxt[maxS], to[maxS];
int edge = 1;

void clear(){
    foreach(0, cnt, i){
        head[i] = 0;
        foreach(0, 25, j) tree[i][j] = 0;
        times[i] = 0;
        fail[i] = 0;
    }
    foreach(0, edge, i) to[i] = nxt[i] = 0;
    foreach(1, n, i){
        ed[i] = 0;
    }
    edge = 1;
    cnt = 0;
}

void add(int u, int v){
    nxt[edge] = head[u];
    to[edge] = v;
    head[u] = edge++;
}

void ins(int i, string s){//把i号目标串插入AC自动机
    int cur = 0;
    for(auto c: s){
        int path = c - 'a';
        if(!tree[cur][path]) tree[cur][path] = ++cnt;
        cur = tree[cur][path];
    }
    ed[i] = cur;
}

void setFail(){//整体设置fail指针，固定优化，设置直通表，防止设置fail指针导致的转圈
    int l = 0, r = 0;
    foreach(0, 25, i){//根节点儿子压入队列
        if(tree[0][i]) box[r++] = tree[0][i];
    }
    while(l < r){
        int u = box[l++];
        foreach(0, 25, i){
            if(tree[u][i]){//有对应儿子
                fail[tree[u][i]] = tree[fail[u]][i];//把父亲fail指针对应的直通表给儿子
                box[r++] = tree[u][i];
            }
            else{
                tree[u][i] = tree[fail[u]][i];//把父亲fail指针给自己
            }
        }
    }
}

void dfs(int x){
    for(int i = head[x]; i; i = nxt[i]){
        int v = to[i];
        dfs(v);
        times[x] += times[v];
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    while(1){
        cin >> n;
        if(!n) break;

        string IN[N];
        foreach(1, n, i){
            string tmp;
            cin >> tmp;
            ins(i, tmp);
            IN[i] = tmp;
        }
        setFail();
        string s;
        cin >> s;
        int u = 0;
        for(auto c: s){
            int path = c - 'a';
            u = tree[u][path];
            times[u]++;
        }
        foreach(1, cnt, i){//利用fail建反图
            add(fail[i], i);
        }
        dfs(0);
        
        int maxn = 0;
        foreach(1, n, i){
            maxn = max(times[ed[i]], maxn);
        }
        cout << maxn << '\n';
        foreach(1, n, i){
            if(maxn == times[ed[i]]){
                cout << IN[i] << '\n';
            }
        }
        clear();
    }
}