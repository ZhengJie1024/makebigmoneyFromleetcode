#include <set>
#include <unordered_map>

// 实现 LFUCache 类：
//
//LFUCache(int capacity) - 用数据结构的容量 capacity 初始化对象
//int get(int key) - 如果键存在于缓存中，则获取键的值，否则返回 -1。
//void put(int key, int value) - 如果键已存在，则变更其值；如果键不存在，请插入键值对。当缓存达到其容量时，则应该在插入新项之前，使最不经常使用的项无效。在此问题中，当存在平局（即两个或更多个键具有相同使用频率）时，应该去除 最近最久未使用 的键。
//注意「项的使用次数」就是自插入该项以来对其调用 get 和 put 函数的次数之和。使用次数会在对应项被移除后置为 0 。
//
//为了确定最不常使用的键，可以为缓存中的每个键维护一个 使用计数器 。使用计数最小的键是最久未使用的键。
//
//当一个键首次插入到缓存中时，它的使用计数器被设置为 1 (由于 put 操作)。对缓存中的键执行 get 或 put 操作，使用计数器的值将会递增。
//
// 
//
//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/lfu-cache
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

// 双hash方法，时间复杂度 o(1)
// 统计 每个键的cnt , cnt 相同的情况下 删除最久的
// 维护一个 map_key = cnt :  map_value = Node, Node 是一个 双向链表
  // 每次put, get 需要找到 Node的节点属于 更新 cnt, 在当前cnt层删除，挪到在下一个cnt层
// 维护 一个 map_key = key : map_value = Node 指针，用于删除

// 这里是平衡二叉树的方法

struct Node {
    int cnt, time, key, value;

    Node(int _cnt, int _time, int _key, int _value):cnt(_cnt), time(_time), key(_key), value(_value){}

    // todo zhengjie 结合 红黑二叉树的set的定义
    // 应该是个顺序
    bool operator < (const Node& rhs) const {
      return cnt == rhs.cnt ? time < rhs.time : cnt < rhs.cnt;
    }
};
class LFUCache {
    // 缓存容量，时间戳
    int capacity, time;
    std::unordered_map<int, Node> key_table;
    std::set<Node> S;
public:
    LFUCache(int _capacity) {
      capacity = _capacity;
      time = 0;
      key_table.clear();
      S.clear();
    }

    int get(int key) {
      if (capacity == 0) return -1;
      auto it = key_table.find(key);
      // 如果哈希表中没有键 key，返回 -1
      if (it == key_table.end()) return -1;
      // 从哈希表中得到旧的缓存
      Node cache = it -> second;
      // 从平衡二叉树中删除旧的缓存
      S.erase(cache);
      // 将旧缓存更新
      cache.cnt += 1;
      cache.time = ++time;
      // 将新缓存重新放入哈希表和平衡二叉树中
      S.insert(cache);
      it -> second = cache;
      return cache.value;
    }

    void put(int key, int value) {
      if (capacity == 0) return;
      auto it = key_table.find(key);
      if (it == key_table.end()) {
        // 如果到达缓存容量上限
        if (key_table.size() == capacity) {
          // 从哈希表和平衡二叉树中删除最近最少使用的缓存
          key_table.erase(S.begin() -> key);
          S.erase(S.begin());
        }
        // 创建新的缓存
        Node cache = Node(1, ++time, key, value);
        // 将新缓存放入哈希表和平衡二叉树中
        key_table.insert(std::make_pair(key, cache));
        S.insert(cache);
      }
      else {
        // 这里和 get() 函数类似
        Node cache = it -> second;
        S.erase(cache);
        cache.cnt += 1;
        cache.time = ++time;
        cache.value = value;
        S.insert(cache);
        it -> second = cache;
      }
    }
};




