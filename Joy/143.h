#include <iostream>

struct ListNode {
 int val;
 ListNode *next;
 ListNode() : val(0), next(nullptr) {}
 ListNode(int x) : val(x), next(nullptr) {}
 ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
// 找中点 ， 链表反转，合并链表
    void reorderList(ListNode* head) {
      // 找中点
      ListNode* cur = head;
      int n = 0;
      while (cur != nullptr) {
        n++;
        cur = cur->next;
      }

      int middle_size = (n + 1) / 2;
      cur = head;
      for (int i = 0; i < middle_size; i++) {
        cur = cur->next;
      }
      // 反转 cur
      ListNode* reverse_linked= reverse(cur);

      cur = head;
      ListNode* tmp = nullptr;
      ListNode* tmp2 = nullptr;

      while (cur != nullptr && reverse_linked != nullptr) {
        tmp = cur->next;
        tmp2 = reverse_linked->next;

        cur->next = reverse_linked;
        reverse_linked->next = tmp;

        cur = tmp;
        reverse_linked = tmp2;
      }
      if (cur) {
        cur->next = nullptr;
      }
      return ;
    }

    ListNode* reverse(ListNode* root) {
      ListNode* head = root;
      ListNode* last = root->next;
      ListNode* tmp = nullptr;
      head->next = nullptr;
      while (last != nullptr) {
        tmp = last;
        last = last->next;
        tmp->next = head;
        head = tmp;
      }
      return head;
    }
};