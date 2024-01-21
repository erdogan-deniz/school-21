#ifndef CPP2_S21_CONTAINERS_S21_LIST_H_
#define CPP2_S21_CONTAINERS_S21_LIST_H_

namespace s21 {
template <typename T>
class List {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  List();
  List(size_type n);
  List(const List &l);
  List(List &&l);
  ~List();

  const_reference front();
  const_reference back();

  void push_front(const_reference value);
  void pop_front();
  void push_back(const_reference value);
  void pop_back();
  T &operator[](const int index);
  void operator=(List &l);
  size_type size() { return this->Size; }
  bool empty() { return this->Size > 0 ? 0 : 1; }
  void swap(List<T> &other);
  void merge(List<T> &other);
  void reverse();
  void unique();
  void sort();
  void clear();

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
  iterator begin();
  iterator end();
  void erase(iterator pos);
  iterator insert(iterator pos, const_reference value);
  void splice(const_iterator pos, List<T> &other);

 private:
  iterator *iter;
};
}  // namespace s21

#include "s21_list.tpp"

#endif  // CPP2_S21_CONTAINERS_S21_LIST_H_