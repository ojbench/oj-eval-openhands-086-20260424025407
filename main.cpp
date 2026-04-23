
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        inorderHelper(root, result);
        return result;
    }
    
    void inorderHelper(TreeNode* node, vector<int> &result) {
        if (node == nullptr) return;
        inorderHelper(node->left, result);
        result.push_back(node->val);
        inorderHelper(node->right, result);
    }
    
    void swapSubtrees(TreeNode* node) {
        if (node == nullptr) return;
        TreeNode* temp = node->left;
        node->left = node->right;
        node->right = temp;
    }
    
    void getNodesAtDepth(TreeNode* root, int targetDepth, vector<TreeNode*> &nodes, int currentDepth = 1) {
        if (root == nullptr) return;
        if (currentDepth == targetDepth) {
            nodes.push_back(root);
            return;
        }
        getNodesAtDepth(root->left, targetDepth, nodes, currentDepth + 1);
        getNodesAtDepth(root->right, targetDepth, nodes, currentDepth + 1);
    }
    
    void processK(TreeNode* root, int k, int n) {
        // For each depth that is a multiple of k, swap subtrees of all nodes at that depth
        for (int depth = k; depth <= n; depth += k) {
            vector<TreeNode*> nodesAtDepth;
            getNodesAtDepth(root, depth, nodesAtDepth);
            for (TreeNode* node : nodesAtDepth) {
                swapSubtrees(node);
            }
        }
    }
};

int main() {
    int n;
    cin >> n;
    
    // Create nodes
    vector<TreeNode*> nodes(n + 1);
    for (int i = 1; i <= n; i++) {
        nodes[i] = new TreeNode(i);
    }
    
    // Read children
    for (int i = 1; i <= n; i++) {
        int left, right;
        cin >> left >> right;
        if (left != -1) {
            nodes[i]->left = nodes[left];
        }
        if (right != -1) {
            nodes[i]->right = nodes[right];
        }
    }
    
    TreeNode* root = nodes[1];
    Solution solution;
    
    int t;
    cin >> t;
    
    for (int i = 0; i < t; i++) {
        int k;
        cin >> k;
        solution.processK(root, k, n);
        vector<int> result = solution.inorderTraversal(root);
        for (int val : result) {
            cout << val << " ";
        }
        cout << endl;
    }
    
    // Clean up memory
    for (int i = 1; i <= n; i++) {
        delete nodes[i];
    }
    
    return 0;
}
