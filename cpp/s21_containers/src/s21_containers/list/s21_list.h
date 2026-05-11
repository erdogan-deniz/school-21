/**
 * @file s21_list.h
 * @brief `s21::List<T>` — doubly-linked list, STL `std::list` parallel.
 *
 * Differs from `s21::vector` in that storage is node-by-node on the
 * heap (each `Node` owns `data` + `ptrNext` + `ptrPrev`). Supports
 * O(1) `push_front` / `pop_front` / `push_back` / `pop_back` plus
 * the canonical list-only ops `merge` / `reverse` / `unique` / `sort`
 * / `splice`.
 *
 * Note the public class name is `List` (not `list`), and `size()` /
 * `empty()` return `int` / `bool` directly rather than via STL
 * `size_type`. Method definitions live in `s21_list.tpp`.
 */

#ifndef CPP2_S21_CONTAINERS_S21_LIST_H_
#define CPP2_S21_CONTAINERS_S21_LIST_H_

namespace s21 {
/**
 * @brief STL-parallel doubly-linked list with head/tail pointers.
 *
 * Iterators come in two flavours: @c iterator (mutable) and
 * @c const_iterator (read-only, currently a thin shim over the
 * mutable variant). Both expose `*`, `->`, pre/post `++` / `--`, and
 * comparison.
 */
template <typename T>
class List {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  /// @name Member functions — construction / destruction
  /// @{
  List();              ///< Default ctor — empty list.
  List(size_type n);   ///< Construct with @p n default-initialised nodes.
  List(const List &l); ///< Copy ctor — deep-copies every node.
  List(List &&l);      ///< Move ctor.
  ~List();             ///< Releases every node.
  /// @}

  /// @name Element access
  /// @{
  const_reference front();  ///< First element (UB if empty).
  const_reference back();   ///< Last element (UB if empty).
  /// @}

  /// @name Modifiers — head / tail
  /// @{
  void push_front(const_reference value);  ///< Prepend; O(1).
  void pop_front();                        ///< Drop the head; O(1).
  void push_back(const_reference value);   ///< Append; O(1).
  void pop_back();                         ///< Drop the tail; O(1).
  /// @}

  /// @name Random access / assignment
  /// @{
  T &operator[](const int index);          ///< Linear-scan random access; O(n).
  void operator=(List &l);                 ///< Copy assignment.
  /// @}

  /// @name Capacity
  /// @{
  size_type size() { return this->Size; }
  bool empty() { return this->Size > 0 ? 0 : 1; }
  /// @}

  /// @name List operations
  /// @{
  void swap(List<T> &other);    ///< O(1) swap.
  void merge(List<T> &other);   ///< Merge two sorted lists into `*this`.
  void reverse();               ///< Reverse the link order in place.
  void unique();                ///< Drop consecutive duplicates.
  void sort();                  ///< In-place sort (merge-sort-ish).
  void clear();                 ///< Drop every node.
  /// @}

 private:
  template <typename>
  class Node {
   public:
    T data;
    Node<T> *ptrNext;
    Node<T> *ptrPrev;

    Node(T data = T(), Node *ptrNext = nullptr, Node *ptrPrev = nullptr) {
      this->data = data;
      this->ptrNext = ptrNext;
      this->ptrPrev = ptrPrev;
    }
  };

  int Size;
  Node<T> *head;
  Node<T> *tail;

  template <typename>
  class ListIterator {
   public:
    Node<T> *ptrIter;

    ListIterator() { ptrIter = nullptr; }
    ListIterator(List<T> &ptr) { ptrIter = ptr.head; }

    T &operator*() {
      try {
        if (!this->ptrIter) throw "Error: There are no elements on the list";
      } catch (const char *e) {
        std::cerr << e << '\n';
        exit(1);
      }

      return ptrIter->data;
    }

    ListIterator operator++() {
      try {
        if (this->ptrIter->ptrNext == nullptr) throw "Error: Out of list";
      } catch (const char *e) {
        std::cerr << e << '\n';
        exit(1);
      }

      ListIterator<T> *tmpPtr = new ListIterator<T>;
      tmpPtr->ptrIter = new Node<T>;
      tmpPtr->ptrIter = this->ptrIter->ptrNext;
      this->ptrIter = tmpPtr->ptrIter;
      return *this;
    }

    ListIterator operator++(int value) {
      value = value;
      try {
        if (this->ptrIter->ptrNext == nullptr) throw "Error: Out of list";
      } catch (const char *e) {
        std::cerr << e << '\n';
        exit(1);
      }

      ListIterator<T> *tmpPtr = new ListIterator<T>;
      tmpPtr->ptrIter = new Node<T>;
      tmpPtr->ptrIter->data = this->ptrIter->data;
      tmpPtr->ptrIter->ptrNext = this->ptrIter->ptrNext;
      tmpPtr->ptrIter->ptrPrev = this->ptrIter->ptrPrev;
      this->ptrIter = this->ptrIter->ptrNext;
      return *tmpPtr;
    }

    ListIterator operator--() {
      try {
        if (this->ptrIter->ptrPrev == nullptr) throw "Error: Out of list";
      } catch (const char *e) {
        std::cerr << e << '\n';
        exit(1);
      }

      ListIterator<T> *tmpPtr = new ListIterator<T>;
      tmpPtr->ptrIter = new Node<T>;
      tmpPtr->ptrIter = this->ptrIter->ptrPrev;
      this->ptrIter = tmpPtr->ptrIter;
      return *this;
    }

    ListIterator operator--(int value) {
      value = value;
      try {
        if (this->ptrIter->ptrPrev == nullptr) throw "Error: Out of list";
      } catch (const char *e) {
        std::cerr << e << '\n';
        exit(1);
      }

      ListIterator<T> *tmpPtr = new ListIterator<T>;
      tmpPtr->ptrIter = new Node<T>;
      tmpPtr->ptrIter->data = this->ptrIter->data;
      tmpPtr->ptrIter->ptrPrev = this->ptrIter->ptrPrev;
      tmpPtr->ptrIter->ptrNext = this->ptrIter->ptrNext;
      this->ptrIter = this->ptrIter->ptrPrev;
      return *tmpPtr;
    }

    bool operator==(ListIterator &other) {
      return this->ptrIter == other.ptrIter;
    }
    bool operator!=(ListIterator &other) {
      return !(this->ptrIter == other.ptrIter);
    }
    bool check_firts() { return this->ptrIter->ptrPrev == nullptr ? 1 : 0; }
    bool check_last() { return this->ptrIter->ptrNext == nullptr ? 1 : 0; }
  };

  template <typename>
  class ListConstIterator : public ListIterator<T> {
   public:
    ListConstIterator() : ListIterator<T>() {}
  };

 public:
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;
  /// @name Iterators + positional ops
  /// @{
  iterator begin();
  iterator end();
  void erase(iterator pos);                              ///< Remove node at @p pos.
  iterator insert(iterator pos, const_reference value);  ///< Insert before @p pos.
  void splice(const_iterator pos, List<T> &other);       ///< Move every node of @p other before @p pos.
  /// @}

 private:
  iterator *iter;
};
}  // namespace s21

#include "s21_list.tpp"

#endif  // CPP2_S21_CONTAINERS_S21_LIST_H_