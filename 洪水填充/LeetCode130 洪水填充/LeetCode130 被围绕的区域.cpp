#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

int m, n;

void dfs(int x, int y, vector<vector<char>> & board){
    if(x<0 || y<0 || x>=m || y>=n || board[x][y]!='O') return;

    board[x][y] = 'F';
    dfs(x+1, y, board);
    dfs(x-1, y, board);
    dfs(x, y+1, board);
    dfs(x, y-1, board);
}

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        m = board.size(), n = board[0].size();
        foreach(0, m-1, i){
            dfs(i, 0, board);
            dfs(i, n-1, board);
        }
        foreach(0, n-1, i){
            dfs(0, i, board);
            dfs(m-1, i, board);
        }
        foreach(0, m-1, i) foreach(0, n-1, j){
            if(board[i][j] == 'O') board[i][j] = 'X';
        }
        foreach(0, m-1, i) foreach(0, n-1, j){
            if(board[i][j] == 'F') board[i][j] = 'O';
        }
    }
};


signed main(){
    Solution slu;
    vector<vector<char>> board = {{'X', 'X', 'X', 'X'}, {'X', 'O', 'O', 'X'}, {'X', 'X', 'O', 'X'}, {'X', 'O', 'X', 'X'}};
    slu.solve(board);
    for(auto &x: board){
        for(auto &y: x) cout << y << ' ';
        cout << '\n';
    }
}