#include <vector>
#include <queue>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {

      priority_queue<pair<int , ListNode*>, vector<pair<int , ListNode*>>, greater<pair<int , ListNode*>>> q; // val to idx

      for (int i = 0; i < lists.size(); i++) {
        if (lists[i] != nullptr) {
          q.emplace(lists[i]->val, lists[i]);
        }
      }
      ListNode* root = nullptr;
      ListNode* cur = nullptr;
      while (!q.empty()) {
        auto min_link = q.top();
        q.pop();

        if (root == nullptr) {
          root = min_link.second;
        }
        if (min_link.second->next) {
          q.emplace(min_link.second->next->val, min_link.second->next);
        }
        if (cur == nullptr) {
          cur = min_link.second;
        } else {
          cur->next = min_link.second;
          cur = cur->next;
        }
      }
      return root;
    }
};
