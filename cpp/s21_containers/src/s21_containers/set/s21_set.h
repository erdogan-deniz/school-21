#ifndef S21_CONTAINERS_SRC_S21_SET_H_
#define S21_CONTAINERS_SRC_S21_SET_H_

namespace s21 {
template <class Key>
class set {
 private:
  struct Node {
    Key value;
    Node *left;
    Node *right;
    Node *parent;

    inline Node(const Key &value) noexcept {
      this->value = value;
      left = nullptr;
      right = nullptr;
      parent = nullptr;
    }
  };

  Node *rootPtr;
  size_t m_size;

 public:
  class iterator {
   public:
    Node *current;

    iterator(Node *current) noexcept { this->current = current; }

    iterator &operator++() {
      if (current == nullptr) return *this;

      if (current->right != nullptr) {
        current = current->right;
        while (current->left != nullptr) current = current->left;
      }

      else {
        Node *parent = current->parent;
        while (parent != nullptr && current == parent->right) {
          current = parent;
          parent = current->parent;
        }
        current = parent;
      }
      return *this;
    }

    iterator operator++(int) {
      iterator temp = *this;
      ++(*this);
      return temp;
    }

    iterator &operator--() {
      if (current == nullptr) return *this;

      if (current->left != nullptr) {
        current = current->left;
        while (current->right != nullptr) current = current->right;
      }

      else {
        Node *parent = current->parent;
        if (parent == nullptr) return *this;
        while (parent != nullptr && current == parent->left) {
          current = parent;
          parent = parent->parent;
        }
        current = parent;
      }

      return *this;
    }

    iterator operator--(int) {
      iterator temp = *this;
      --(*this);
      return temp;
    }

    Key &operator*() const { return current->value; }

    bool operator==(const iterator &other) const {
      return current == other.current;
    }

    bool operator!=(const iterator &other) const { return !(*this == other); }
  };

  class const_iterator {
   public:
    const Node *current;

    const_iterator(const Node *current) : current(current) {}

    const_iterator &operator++() {
      if (current == nullptr) return *this;

      if (current->right != nullptr) {
        current = current->right;
        while (current->left != nullptr) current = current->left;
      }

      else {
        const Node *parent = current->parent;
        while (parent != nullptr && current == parent->right) {
          current = parent;
          parent = current->parent;
        }
        current = parent;
      }
      return *this;
    }

    const_iterator &operator--() {
      if (current == nullptr) return *this;

      if (current->left != nullptr) {
        current = current->left;
        while (current->right != nullptr) current = current->right;
      }

      else {
        const Node *parent = current->parent;
        if (parent == nullptr) return *this;
        while (parent != nullptr && current == parent->left) {
          current = parent;
          parent = parent->parent;
        }
        current = parent;
      }

      return *this;
    }

    const_iterator operator++(int) {
      const_iterator temp = *this;
      ++(*this);
      return temp;
    }

    const_iterator operator--(int) {
      const_iterator temp = *this;
      --(*this);
      return temp;
    }

    const Key &operator*() const { return current->value; }

    bool operator==(const const_iterator &other) const {
      return current == other.current;
    }

    bool operator!=(const const_iterator &other) const {
      return !(*this == other);
    }
  };

  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  set() noexcept {
    rootPtr = nullptr;
    m_size = 0;
  }

  set(std::initializer_list<value_type> const &items) : set() {
    for (const auto &item : items) insert(item);
  }

  set(const set &s) : set() {
    for (const auto &item : s) insert(item);
  }

  set(set &&s) : set() { swap(s); }

  ~set() { clear(); }

  set &operator=(set &&s) {
    swap(s);
    return *this;
  }

  iterator begin() const {
    Node *current = rootPtr;
    while (current != nullptr && current->left != nullptr)
      current = current->left;

    return iterator(current);
  }

  inline iterator end() const { return iterator(nullptr); }

  inline bool empty() const noexcept { return m_size == 0; }

  inline size_type size() noexcept { return m_size; }

  inline size_type max_size() const { return std::numeric_limits<int>::max(); }

  void clear() {
    clear(rootPtr);
    rootPtr = nullptr;
    m_size = 0;
  }

  inline std::pair<iterator, bool> insert(const value_type &value) {
    if (rootPtr == nullptr) {
      rootPtr = new Node(value);
      ++m_size;
      return {iterator(rootPtr), true};
    }

    Node *current = rootPtr;
    Node *parent = nullptr;

    while (current != nullptr) {
      if (value < current->value) {
        parent = current;
        current = current->left;
      } else if (current->value < value) {
        parent = current;
        current = current->right;
      } else
        return {iterator(current), false};
    }

    if (value < parent->value) {
      parent->left = new Node(value);
      parent->left->parent = parent;
      ++m_size;
      return {iterator(parent->left), true};
    } else {
      parent->right = new Node(value);
      parent->right->parent = parent;
      ++m_size;
      return {iterator(parent->right), true};
    }
  }

  void erase(iterator pos) {
    Node *current = pos.current;
    if (pos.current == nullptr) return;
    --m_size;
    if (current->left == nullptr && current->right == nullptr) {
      if (current->parent == nullptr)
        rootPtr = nullptr;

      else if (pos.current == current->parent->left)
        current->parent->left = nullptr;

      else
        current->parent->right = nullptr;
      delete pos.current;
    }

    else if (current->left == nullptr || current->right == nullptr) {
      Node *child = current->left != nullptr ? current->left : current->right;
      child->parent = current->parent;
      if (current->parent == nullptr)
        rootPtr = child;

      else if (current == current->parent->left)
        current->parent->left = child;

      else
        current->parent->right = child;

      delete pos.current;
    }

    else {
      Node *successor = current->right;
      while (successor->left != nullptr) successor = successor->left;

      current->value = successor->value;
      erase(iterator(successor));
    }
  }

  void swap(set &other) {
    std::swap(rootPtr, other.rootPtr);
    std::swap(m_size, other.m_size);
  }

  void merge(set &other) {
    if (&other != this) {
      for (const auto &item : other) insert(item);

      other.clear();
    }
  }

  iterator find(const Key &key) {
    Node *current = rootPtr;

    while (current != nullptr) {
      if (key < current->value)
        current = current->left;

      else if (current->value < key)
        current = current->right;

      else
        return iterator(current);
    }

    return iterator(nullptr);
  }

  inline bool contains(const Key &key) { return find(key) != end(); }

 private:
  void clear(Node *current) {
    if (current != nullptr) {
      clear(current->left);
      clear(current->right);
      delete current;
    }
  }
};

template <typename Key, typename... Args>
void insert_many(set<Key> &s, Args &&...args) {
  (void)std::initializer_list<int>{(s.insert(std::forward<Args>(args)), 0)...};
}

}  // namespace s21

#endif  //  S21_CONTAINERS_SRC_S21_SET_H_
