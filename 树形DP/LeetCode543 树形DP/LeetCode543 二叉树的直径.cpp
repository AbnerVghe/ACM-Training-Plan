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
    int lenRoot, lenNRoot;
};

Info dp(TreeNode* root){
    if(root == nullptr) return (Info){0, 0};

    Info infol = dp(root->left), infor = dp(root->right);
    int lenRoot = max(infol.lenRoot, infor.lenRoot) + 1;
    int lenNRoot = max(infol.lenRoot+infor.lenRoot, max(infol.lenNRoot, infor.lenNRoot));
    return (Info){lenRoot, lenNRoot};
};

class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        Info info = dp(root);
        return info.lenNRoot;
    }
};