#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
using namespace std;
#define INF 0x3f3f3f3f

// * Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
   TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

const int N = 1e5+7;
int dfn[N];
int sz[N], dep[N];
int cntD;
//int n;

void dfs(TreeNode* x, int k){
    int id = ++cntD;
    dfn[x->val] = id;
    int tmpSz = 1;
    if(x->left != nullptr){
        dfs(x->left, k+1);
        tmpSz += sz[dfn[x->left->val]];
    }
    if(x->right != nullptr){
        dfs(x->right, k+1);
        tmpSz += sz[dfn[x->right->val]];
    }   
    dep[id] = k;
    sz[id] = tmpSz;
    //n = max(n, x->val);
}

int maxL[N], maxR[N];

class Solution {
public:
    vector<int> treeQueries(TreeNode* root, vector<int>& queries){
        cntD = 0;
        dfs(root, 0);
        maxL[0] = maxR[cntD+1] = 0;
        foreach(1, cntD, i) maxL[i] = max(maxL[i-1], dep[i]);
        foreach_sub(cntD, 1, i) maxR[i] = max(maxR[i+1], dep[i]);
        vector<int> ans;
        for(auto query: queries){
            int l = dfn[query];
            int r = l + sz[l] - 1;
            ans.push_back(max(maxL[l-1], maxR[r+1]));
        }
        return ans;
    }
};