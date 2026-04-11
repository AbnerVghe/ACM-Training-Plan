#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;

const int N = 510;

int n;
int cnt = 1, sz[N*N];
int ans = 0;
bool vis[N*N];

void dfs(int x, int y, int id, vector<vector<int>>& grid){
    if(x<0 || y<0 || x>= n || y>=n || grid[x][y]!=1) return;

    grid[x][y] = id;
    sz[id]++;
    dfs(x+1, y, id, grid);
    dfs(x-1, y, id, grid);
    dfs(x, y+1, id, grid);
    dfs(x, y-1, id, grid);
}

class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        n = grid.size();
        memset(vis, 0, sizeof vis);
        memset(sz, 0, sizeof sz);
        foreach(0, n-1, i) foreach(0, n-1, j){
            if(grid[i][j] == 1) dfs(i, j, ++cnt, grid);
        }

        foreach(2, cnt, i) ans = max(ans, sz[i]);

        foreach(0, n-1, i) foreach(0, n-1, j){
            if(grid[i][j] == 0){
                int up, down, left, right;
                up = (i-1 < 0) ? 0 : grid[i-1][j];
                down = (i+1 >= n) ? 0 : grid[i+1][j];
                left = (j-1 < 0) ? 0 : grid[i][j-1];
                right = (j+1 >= n) ? 0 : grid[i][j+1];

                int sum = 1;
                vis[up] = 1;
                sum += sz[up];
                if(!vis[down]){
                    vis[down] = 1;
                    sum += sz[down];
                }
                if(!vis[left]){
                    vis[left] = 1;
                    sum += sz[left];
                }
                if(!vis[right]){
                    vis[right] = 1;
                    sum += sz[right];
                }
                ans = max(ans, sum);
                vis[up] = vis[down] = vis[left] = vis[right] = 0;
            }
        }

        return ans;
    }
};

signed main(){
    Solution slu;
    vector<vector<int>> grid = {{0, 0}, {0, 0}};
    cout << slu.largestIsland(grid) << ' ';
    cout << sz[0];
}