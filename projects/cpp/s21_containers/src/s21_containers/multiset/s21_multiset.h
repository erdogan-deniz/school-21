#ifndef S21_CONTAINERS_SRC_S21_MULTISET_H_
#define S21_CONTAINERS_SRC_S21_MULTISET_H_

namespace s21 {
template <typename Key>
class multiset {
 private:
  struct Node {
    Key key;
    size_t count;
    Node *left;
    Node *right;
    Node *parent;

    Node(Key key)
        : key(key), count(1), left(nullptr), right(nullptr), parent(nullptr) {}
  };

  Node *rootPtr;
  size_t m_size;

  void clear(Node *node) {
    if (node == nullptr) {
      return;
    }
    clear(node->left);
    clear(node->right);
    delete node;
  }

  inline Node *copy(Node *node, Node *parent) {
    if (node == nullptr) return nullptr;

    Node *new_node = new Node(node->key);
    new_node->count = node->count;
    new_node->left = copy(node->left, new_node);
    new_node->right = copy(node->right, new_node);
    new_node->parent = parent;
    return new_node;
  }

  void erase_node(Node *node) {
    if (node->left == nullptr && node->right == nullptr) {
      if (node->parent == nullptr)
        rootPtr = nullptr;

      else if (node->parent->left == node)
        node->parent->left = nullptr;

      else
        node->parent->right = nullptr;

    }

    else if (node->left == nullptr) {
      if (node->parent == nullptr) {
        rootPtr = node->right;
        rootPtr->parent = nullptr;
      }

      else if (node->parent->left == node) {
        node->parent->left = node->right;
        node->right->parent = node->parent;
      }

      else {
        node->parent->right = node->right;
        node->right->parent = node->parent;
      }
    }

    else if (node->right == nullptr) {
      if (node->parent == nullptr) {
        rootPtr = node->left;
        rootPtr->parent = nullptr;
      }

      else if (node->parent->left == node) {
        node->parent->left = node->left;
        node->left->parent = node->parent;
      }

      else {
        node->parent->right = node->left;
        node->left->parent = node->parent;
      }
    }

    else {
      Node *successor = node->right;
      while (successor->left != nullptr) successor = successor->left;

      node->key = successor->key;
      node->count = successor->count;
      erase_node(successor);
    }
    delete node;
  }

  Node *find_node(const Key &key) const {
    Node *current = rootPtr;
    while (current != nullptr) {
      if (key < current->key)
        current = current->left;
      else if (key > current->key)
        current = current->right;
      else
        return current;
    }
    return nullptr;
  }

  Node *lower_bound_helper(const Key &key) const {
    Node *current = rootPtr;
    Node *lower_bound = nullptr;
    while (current != nullptr) {
      if (key <= current->key) {
        lower_bound = current;
        current = current->left;
      }

      else
        current = current->right;
    }
    return lower_bound;
  }

  Node *upper_bound_helper(const Key &key) const {
    Node *current = rootPtr;
    Node *upper_bound = nullptr;
    while (current != nullptr) {
      if (key < current->key) {
        upper_bound = current;
        current = current->left;
      }

      else
        current = current->right;
    }
    return upper_bound;
  }

  void merge_helper(multiset &other, Node *node) {
    if (node != nullptr) {
      insert(node->key);
      merge_helper(other, node->left);
      merge_helper(other, node->right);
      other.erase_node(node);
    }
  }

 public:
  class iterator {
   public:
    Node *node;

    iterator(Node *node) : node(node) {}

    iterator &operator++() {
      if (node->right == nullptr) {
        while (node->parent != nullptr && node->parent->right == node)
          node = node->parent;

        node = node->parent;
      }

      else {
        node = node->right;
        while (node->left != nullptr) node = node->left;
      }
      return *this;
    }

    iterator operator++(int) {
      iterator temp = *this;
      ++(*this);
      return temp;
    }

    iterator &operator--() {
      if (node->left == nullptr) {
        while (node->parent != nullptr && node->parent->left == node)
          node = node->parent;
        node = node->parent;
      }

      else {
        node = node->left;
        while (node->right != nullptr) node = node->right;
      }
      return *this;
    }

    iterator operator--(int) {
      iterator temp = *this;
      --(*this);
      return temp;
    }

    Key &operator*() const { return node->key; }

    Key *operator->() const { return &(node->key); }

    bool operator==(const iterator &other) const { return node == other.node; }

    bool operator!=(const iterator &other) const { return node != other.node; }
  };

  class const_iterator {
   private:
    const Node *node;

   public:
    const_iterator(const Node *node) : node(node) {}

    const_iterator &operator++() {
      if (node->right == nullptr) {
        while (node->parent != nullptr && node->parent->right == node)
          node = node->parent;

        node = node->parent;
      }

      else {
        node = node->right;
        while (node->left != nullptr) node = node->left;
      }
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator temp = *this;
      ++(*this);
      return temp;
    }

    const_iterator &operator--() {
      if (node->left == nullptr) {
        while (node->parent != nullptr && node->parent->left == node)
          node = node->parent;

        node = node->parent;
      }

      else {
        node = node->left;
        while (node->right != nullptr) node = node->right;
      }
      return *this;
    }

    const_iterator operator--(int) {
      const_iterator temp = *this;
      --(*this);
      return temp;
    }

    const Key &operator*() const { return node->key; }

    const Key *operator->() const { return &(node->key); }

    bool operator==(const const_iterator &other) const {
      return node == other.node;
    }

    bool operator!=(const const_iterator &other) const {
      return node != other.node;
    }
  };

  multiset() noexcept : rootPtr(nullptr), m_size(0) {}

  multiset(std::initializer_list<Key> const &items) : multiset() {
    for (const Key &item : items) insert(item);
  }

  multiset(const multiset &ms)
      : rootPtr(copy(ms.rootPtr, nullptr)), m_size(ms.m_size) {}

  multiset(multiset &&ms) : rootPtr(ms.rootPtr), m_size(ms.m_size) {
    ms.rootPtr = nullptr;
    ms.m_size = 0;
  }

  ~multiset() { clear(); }

  multiset &operator=(multiset &&ms) {
    clear();
    rootPtr = ms.rootPtr;
    m_size = ms.m_size;
    ms.rootPtr = nullptr;
    ms.m_size = 0;
    return *this;
  }

  iterator begin() const noexcept {
    Node *current = rootPtr;
    while (current != nullptr && current->left != nullptr)
      current = current->left;

    return iterator(current);
  }

  inline iterator end() const noexcept { return iterator(nullptr); }

  inline bool empty() const noexcept { return m_size == 0; }

  inline size_t size() const noexcept { return m_size; }

  inline size_t max_size() { return std::numeric_limits<size_t>::max(); }

  inline void clear() {
    clear(rootPtr);
    rootPtr = nullptr;
    m_size = 0;
  }

  iterator insert(const Key &value) {
    Node *current = rootPtr;
    Node *parent = nullptr;
    while (current != nullptr) {
      parent = current;
      if (value < current->key)
        current = current->left;
      else
        current = current->right;
    }
    Node *node = new Node(value);
    node->parent = parent;
    if (parent == nullptr)
      rootPtr = node;
    else if (value < parent->key)
      parent->left = node;
    else
      parent->right = node;
    m_size++;
    return iterator(node);
  }

  inline void erase(iterator pos) {
    Node *node = pos.node;
    erase_node(node);
    m_size--;
  }

  inline void swap(multiset &other) {
    std::swap(rootPtr, other.rootPtr);
    std::swap(m_size, other.m_size);
  }

  inline void merge(multiset &other) {
    if (this != &other) merge_helper(other, other.rootPtr);

    other.clear();
  }

  size_t count(const Key &key) const {
    size_t count = 0;
    Node *current = rootPtr;
    while (current != nullptr) {
      if (key == current->key) count += current->count;

      if (key < current->key)
        current = current->left;

      else
        current = current->right;
    }
    return count;
  }

  inline iterator find(const Key &key) const {
    Node *node = find_node(key);
    return iterator(node);
  }

  inline bool contains(const Key &key) const {
    return find_node(key) != nullptr;
  }

  inline std::pair<iterator, iterator> equal_range(const Key &key) const {
    return std::make_pair(iterator(lower_bound(key)),
                          iterator(upper_bound(key)));
  }

  inline iterator lower_bound(const Key &key) const {
    Node *node = lower_bound_helper(key);
    return iterator(node);
  }

  inline iterator upper_bound(const Key &key) const {
    Node *node = upper_bound_helper(key);
    return iterator(node);
  }
};

template <typename Key, typename... Args>
void insert_many(multiset<Key> &ms, Args &&...args) {
  (void)std::initializer_list<int>{
      ((void)ms.insert(std::forward<Args>(args)), 0)...};
}

}  // namespace s21

#endif  //  S21_CONTAINERS_SRC_S21_MULTISET_H_
