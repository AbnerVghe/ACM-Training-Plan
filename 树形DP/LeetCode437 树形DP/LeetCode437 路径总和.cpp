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

unordered_map<ll, int> presum;

int dp(TreeNode* x, int target, ll sum){
    if(x == nullptr) return 0;

    sum += x->val;
    int ans = presum[sum - target];
    presum[sum] += 1;
    ans += dp(x->left, target, sum);
    ans += dp(x->right, target, sum);
    presum[sum] -= 1;
    return ans;
}

class Solution {
public:
    int pathSum(TreeNode* root, int targetSum) {
        presum[0L] = 1;
        return dp(root, targetSum, 0);
    }
};