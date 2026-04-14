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
    int maxn, minn, sum, maxsum;
    bool isBST;
};

Info dp(TreeNode *root){
    if(root == nullptr) return (Info){INT_MIN, INT_MAX, 0, 0, 1};

    Info infol = dp(root->left), infor = dp(root->right);
    int maxn = max(root->val, max(infol.maxn, infor.maxn));
    int minn = min(root->val, min(infol.minn, infor.minn));
    int sum = root->val + infol.sum + infor.sum;
    bool isBST = infol.isBST && infor.isBST && infol.maxn < root->val && infor.minn > root->val;
    int maxsum = INT_MIN;
    if(isBST){
        maxsum = infol.sum + infor.sum + root->val;
    }
    maxsum = max(maxsum, max(infol.maxsum, infor.maxsum));
    return (Info){maxn, minn, sum, maxsum, isBST};
}

class Solution {
public:
    int maxSumBST(TreeNode* root) {
        return dp(root).maxsum;
    }
};