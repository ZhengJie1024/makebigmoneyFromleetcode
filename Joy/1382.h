#include <vector>
#include <stack>
using namespace std;


struct TreeNode {
 int val;
 TreeNode *left;
 TreeNode *right;
 TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* balanceBST(TreeNode* root) {
		if (root == nullptr) {return root;}
	   	vector<TreeNode*> v;
		stack<TreeNode*> s;
	 	while(root->left != nullptr) {
			s.push(root);
		}
		while(!s.empty()){
			auto* cur = s.top();
			s.pop();
			v.push_back(cur);
			if (cur->right){
				cur = cur->right;
				s.push(cur);
				while (cur->left!=nullptr) {
					cur = cur->left;
					s.push(cur);
				}
			}
		}
		return dfs(v, 0, v.size());
    }

	TreeNode* dfs(vector<TreeNode*>& v, int l,int r) {
		if ( l >= r || r <= 0 || l < 0) {
			return nullptr;
		} else if (l + 1 == r) {
			v[l]->left = nullptr;
			v[l]->right = nullptr;
			return v[l];
		} else {
			int m = l + ( r - l ) / 2;
			auto* root = v[m];
			root->left = dfs(v, l, m);
			root->right = dfs(v,m+1, r)
			return root;
		}
	}
};
