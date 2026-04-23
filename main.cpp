
#include &lt;iostream&gt;
#include &lt;vector&gt;
#include &lt;queue&gt;
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector&lt;int&gt; inorderTraversal(TreeNode* root) {
        vector&lt;int&gt; result;
        inorderHelper(root, result);
        return result;
    }
    
    void inorderHelper(TreeNode* node, vector&lt;int&gt; &amp;result) {
        if (node == nullptr) return;
        inorderHelper(node-&gt;left, result);
        result.push_back(node-&gt;val);
        inorderHelper(node-&gt;right, result);
    }
    
    void swapSubtrees(TreeNode* node) {
        if (node == nullptr) return;
        TreeNode* temp = node-&gt;left;
        node-&gt;left = node-&gt;right;
        node-&gt;right = temp;
    }
    
    void getNodesAtDepth(TreeNode* root, int targetDepth, vector&lt;TreeNode*&gt; &amp;nodes, int currentDepth = 1) {
        if (root == nullptr) return;
        if (currentDepth == targetDepth) {
            nodes.push_back(root);
            return;
        }
        getNodesAtDepth(root-&gt;left, targetDepth, nodes, currentDepth + 1);
        getNodesAtDepth(root-&gt;right, targetDepth, nodes, currentDepth + 1);
    }
    
    void processK(TreeNode* root, int k, int n) {
        // For each depth that is a multiple of k, swap subtrees of all nodes at that depth
        for (int depth = k; depth &lt;= n; depth += k) {
            vector&lt;TreeNode*&gt; nodesAtDepth;
            getNodesAtDepth(root, depth, nodesAtDepth);
            for (TreeNode* node : nodesAtDepth) {
                swapSubtrees(node);
            }
        }
    }
};

int main() {
    int n;
    cin &gt;&gt; n;
    
    // Create nodes
    vector&lt;TreeNode*&gt; nodes(n + 1);
    for (int i = 1; i &lt;= n; i++) {
        nodes[i] = new TreeNode(i);
    }
    
    // Read children
    for (int i = 1; i &lt;= n; i++) {
        int left, right;
        cin &gt;&gt; left &gt;&gt; right;
        if (left != -1) {
            nodes[i]-&gt;left = nodes[left];
        }
        if (right != -1) {
            nodes[i]-&gt;right = nodes[right];
        }
    }
    
    TreeNode* root = nodes[1];
    Solution solution;
    
    int t;
    cin &gt;&gt; t;
    
    for (int i = 0; i &lt; t; i++) {
        int k;
        cin &gt;&gt; k;
        solution.processK(root, k, n);
        vector&lt;int&gt; result = solution.inorderTraversal(root);
        for (int val : result) {
            cout &lt;&lt; val &lt;&lt; " ";
        }
        cout &lt;&lt; endl;
    }
    
    // Clean up memory
    for (int i = 1; i &lt;= n; i++) {
        delete nodes[i];
    }
    
    return 0;
}
