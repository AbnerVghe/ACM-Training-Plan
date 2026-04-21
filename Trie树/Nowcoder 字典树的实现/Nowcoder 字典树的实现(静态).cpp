#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 3e6+7;
int cnt = 1, pass[N], ed[N];
unordered_map<int, int> tree[N];

void build(){
    cnt = 1;
}

void ins(string s){
    int cur = 1;
    pass[cur]++;
    for(auto c: s){
        int path = c;
        if(!tree[cur][path]) tree[cur][path] = ++cnt;
        cur = tree[cur][path];
        pass[cur]++;
    }
    ed[cur]++;
}

int search(string s){
    int cur = 1;
    for(auto c: s){
        int path = c;
        if(!tree[cur][path]) return 0;
        cur = tree[cur][path];
    }
    return ed[cur];
}

int search_pre(string s){
    int cur = 1;
    for(auto c: s){
        int path = c;
        if(!tree[cur][path]) return 0;
        cur = tree[cur][path];
    }
    return pass[cur];
}

void del(string s){
    if(search(s) > 0){
        int cur = 1;
        for(auto c: s){
            int path = c;
            int &nxt = tree[cur][path];
            if(--pass[nxt] == 0){
                nxt = 0;
                return;
            }
            cur = nxt;
        }
        ed[cur]--;
    }
}

void clr(){//多个测试用例时，在每个测试用例的末端均清空
    foreach(1, cnt, i){
        tree[i].clear();
        ed[i] = 0;
        pass[i] = 0;
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int T;
    cin >> T;
    while(T--){
        int n, q;
        cin >> n >> q;
        build();
        foreach(1, n, i){
            string tmp;
            cin >> tmp;
            ins(tmp);
        }
        foreach(1, q, j){
            string tmp;
            cin >> tmp;
            cout << search_pre(tmp) << '\n';
        }
        clr();
    }
}