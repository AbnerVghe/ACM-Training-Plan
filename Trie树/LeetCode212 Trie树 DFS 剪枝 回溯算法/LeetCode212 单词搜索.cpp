#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

const int N = 1e5+7;
int tree[N][26], pass[N];
int cnt;
string ed[N];

vector<string> ans;

void build(vector<string>& words){
    cnt = 1;
    pass[0] = 0;
    for(auto word: words){
        int cur = 1;
        pass[cur]++;
        for(auto c: word){
            int path = c - 'a';
            if(!tree[cur][path]) tree[cur][path] = ++cnt;
            cur = tree[cur][path];
            pass[cur]++;
        }
        ed[cur] = word;
    }
}

void clr(){
    foreach(1, cnt, i){
        foreach(0, 25, j) tree[i][j] = 0;
        pass[i] = 0;
        ed[i] = "";
    }
}

int dfs(vector<vector<char>>& board, int i, int j, int t){//t:还没到的时候的编号
    if(i<0 || j<0 || i>=board.size() || j>=board[0].size() || !board[i][j]) return 0;
    
    char tmp = board[i][j];
    int path = tmp - 'a';
    t = tree[t][path];
    if(!pass[t]) return 0;
    int fix = 0;
    if(ed[t] != ""){
        fix++;
        ans.push_back(ed[t]);
        ed[t] = "";
    }

    board[i][j] = 0;
    fix += dfs(board, i+1, j, t);
    fix += dfs(board, i-1, j, t);
    fix += dfs(board, i, j+1, t);
    fix += dfs(board, i, j-1, t);
    board[i][j] = tmp;
    pass[t] -= fix;
    return fix;
}

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        ans.clear();
        build(words);
        foreach(0, board.size()-1, i){
            foreach(0, board[0].size()-1, j){
                dfs(board, i, j, 1);
            }
        }
        clr();
        return ans;
    }
};