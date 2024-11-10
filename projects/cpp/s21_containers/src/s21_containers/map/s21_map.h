#ifndef S21_CONTAINERS_SRC_S21_MAP_H_
#define S21_CONTAINERS_SRC_S21_MAP_H_

namespace s21 {
template <typename Key, typename T>
class map {
 public:
  using value_type = std::pair<const Key, T>;
  using reference = value_type &;
  using const_reference = const value_type &;

  struct Node {
    value_type data;
    Node *left;
    Node *right;
    Node *parent;

    inline Node(const value_type &data) noexcept
        : data(data), left(nullptr), right(nullptr), parent(nullptr) {}
  };

  class iterator {
   public:
    inline iterator(Node *current = nullptr) noexcept : current_(current) {}

    reference operator*() const noexcept { return current_->data; }
    const Node *operator->() const noexcept { return current_; }

    iterator &operator++() noexcept {
      if (current_->right) {  // if there is a right subtree, go to
                              // the minimum element in it
        current_ = getMinNode(current_->right);
      } else {  // otherwise, we find the first parent whose current node is not
                // located in the right subtree
        Node *prev = current_;
        current_ = current_->parent;
        while (current_ && current_->right == prev) {
          prev = current_;
          current_ = current_->parent;
        }
      }
      return *this;
    }
    iterator operator++(int) noexcept {
      iterator temp = *this;
      ++(*this);
      return temp;
    }

    iterator &operator--() noexcept {
      if (current_->left)  // if there is a left subtree, go to
                           // the minimum element in it
        current_ = getMinNode(current_->left);

      else {  // otherwise, we find the first parent whose current node is not
              // located in the left subtree
        Node *prev = current_;
        current_ = current_->parent;
        while (current_ && current_->left == prev) {
          prev = current_;
          current_ = current_->parent;
        }
      }
      return *this;
    }

    iterator operator--(int) {
      iterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const iterator &other) const noexcept {
      return current_ == other.current_;
    }
    bool operator!=(const iterator &other) const noexcept {
      return current_ != other.current_;
    }

   private:
    Node *current_;

    Node *getMinNode(Node *node) const noexcept {
      Node *current = node;
      while (current->left) current = current->left;
      return current;
    }
  };
  // default constructor, creates empty map
  map() noexcept { rootPtr = nullptr, m_size = 0; }
  // initializer list constructor, creates the map initizialized using
  // std::initializer_list
  map(std::initializer_list<value_type> const &items) : map() {
    for (const auto &item : items) insert(item);
  }
  // copy constructor
  map(const map &other) : map() {
    for (const auto &item : other) insert(item);
  }
  // move constructor
  map(map &&other) : map() { swap(other); }
  // destructor
  ~map() { clear(); }

  map &operator=(const map &other) {
    clear();
    for (const auto &item : other) insert(item);
    return *this;
  }
  // assignment operator overload for moving object
  map &operator=(map &&other) {
    clear();
    swap(other);
    return *this;
  }

  // access specified element with bounds checking
  inline T &at(const Key &key) const {
    Node *node = findNode(key, rootPtr);
    if (node)
      return node->data.second;
    else
      throw std::out_of_range("Key not found");
  }

  // access or insert specified element
  inline T &operator[](const Key &key) {
    Node *node = findNode(key, rootPtr);
    if (node)
      return node->data.second;
    else {
      value_type newKeyValue = std::make_pair(key, T());
      insert(newKeyValue);
      return findNode(key, rootPtr)->data.second;
    }
  }

  // returns an iterator to the beginning
  inline iterator begin() const {
    if (rootPtr != nullptr) return iterator(getMinNode(rootPtr));

    return end();
  }
  // returns an iterator to the end
  inline iterator end() const noexcept { return iterator(nullptr); }

  // checks whether the container is empty
  inline bool empty() const noexcept { return m_size == 0; }
  // returns the number of elements
  inline size_t size() const noexcept { return m_size; }
  // returns the maximum possible number of elements
  inline size_t max_size() const { return std::numeric_limits<size_t>::max(); }

  // clears the contents
  inline void clear() {
    clearNodes(rootPtr);
    m_size = 0;
  }

  // inserts node and returns iterator to where the element is in the container
  // and bool denoting whether the insertion took place
  std::pair<iterator, bool> insert(const value_type &value) {
    Node *newNode = new Node(value);
    Node *parent = nullptr;
    Node *current = rootPtr;

    while (current) {
      parent = current;
      if (value.first < current->data.first)
        current = current->left;

      else if (value.first > current->data.first)
        current = current->right;

      else {
        delete newNode;
        return std::make_pair(iterator(current), false);
      }
    }

    newNode->parent = parent;

    if (!parent)
      rootPtr = newNode;

    else if (value.first < parent->data.first)
      parent->left = newNode;

    else
      parent->right = newNode;

    m_size++;
    return std::make_pair(iterator(newNode), true);
  }

  // inserts value by key and returns iterator to where the element is in the
  // container and bool denoting whether the insertion took place
  std::pair<iterator, bool> insert(const Key &key, const T &obj) {
    return insert(std::make_pair(key, obj));
  }

  // inserts an element or assigns to the current element if the key already
  // exists
  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
    Node *node = findNode(key, rootPtr);
    if (node) {
      node->data.second = obj;
      return std::make_pair(iterator(node), false);
    } else
      return insert(std::make_pair(key, obj));
  }

  // erases element at pos
  void erase(iterator pos) {
    const Node *node = pos.operator->();

    // if the node being deleted has no children or has only one child
    if (!node->left)
      transplant(const_cast<Node *>(node), const_cast<Node *>(node->right));
    else if (!node->right)
      transplant(const_cast<Node *>(node), const_cast<Node *>(node->left));

    else {  // if the node being deleted has two children, replace it with the
            // next node in sorted order
      Node *successor = getMinNode(const_cast<Node *>(node->right));
      if (successor->parent != node) {
        transplant(const_cast<Node *>(successor),
                   const_cast<Node *>(successor->right));
        successor->right = node->right;
        successor->right->parent = successor;
      }
      transplant(const_cast<Node *>(node), const_cast<Node *>(successor));
      successor->left = node->left;
      successor->left->parent = successor;
    }

    delete node;
    m_size--;
  }

  // swaps the contents
  inline void swap(map &other) {
    std::swap(rootPtr, other.rootPtr);
    std::swap(m_size, other.m_size);
  }

  // splices nodes from another container
  void merge(map &other) {
    if (this != &other) {
      for (const auto &item : other) insert(item);
      other.clear();
    }
  }

  bool contains(const Key &key) const noexcept {
    Node *current = rootPtr;

    while (current != nullptr) {
      if (key == current->data.first)
        return true;
      else if (key < current->data.first)
        current = current->left;
      else
        current = current->right;
    }

    return false;
  }

 private:
  Node *rootPtr;
  size_t m_size;

  inline Node *findNode(const Key &key, Node *node) const {
    if (node == nullptr || key == node->data.first) return node;
    if (key < node->data.first)
      return findNode(key, node->left);
    else
      return findNode(key, node->right);
  }

  inline void clearNodes(Node *&node) {
    if (node != nullptr) {
      clearNodes(node->left);
      clearNodes(node->right);
      delete node;
      node = nullptr;
    }
  }

  Node *getMinNode(Node *node) const {
    Node *current = node;

    while (current->left) current = current->left;

    return current;
  }

  inline void transplant(Node *oldNode, Node *newNode) {
    if (!oldNode->parent)
      rootPtr = newNode;

    else if (oldNode == oldNode->parent->left)
      oldNode->parent->left = newNode;

    else
      oldNode->parent->right = newNode;

    if (newNode) newNode->parent = oldNode->parent;
  }
};

template <typename... Args>
inline void insert_many(map<int, std::string> &myMap, Args &&...args) {
  (myMap.insert(std::forward<Args>(args)), ...);
}

}  // namespace s21

#endif  //  S21_CONTAINERS_SRC_S21_MAP_H_
