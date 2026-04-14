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


struct Info{
    int cnt, sum, move;
};

Info dp(TreeNode* root){
    if(root == nullptr) return (Info){0, 0, 0};

    Info infol = dp(root->left), infor = dp(root->right);
    int cnt = infol.cnt + infor.cnt + 1;
    int sum = infol.sum + infor.sum + root->val;
    int move = infol.move + infor.move + fabs(infol.sum-infol.cnt) + fabs(infor.sum-infor.cnt);
    return (Info){cnt, sum, move};
}

class Solution {
public:
    int distributeCoins(TreeNode* root) {
        return dp(root).move;
    }
};