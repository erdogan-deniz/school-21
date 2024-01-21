#ifndef CPP2_S21_CONTAINERS_S21_STACK_H_
#define CPP2_S21_CONTAINERS_S21_STACK_H_

namespace s21 {
template <typename T>
class Stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  Stack();
  Stack(const Stack &s);
  Stack(Stack &&s);
  ~Stack();
  void operator=(Stack &s);

  const_reference top();

  size_type size() { return this->Size; }
  bool empty() { return this->size() ? 0 : 1; }

  void push(const_reference value);
  void pop();
  void swap(Stack<T> &other);

 private:
  template <typename>
  class Node {
   public:
    T data;
    Node *ptrNext;

    Node(T data = T(), Node *ptrNext = nullptr) {
      this->data = data;
      this->ptrNext = ptrNext;
    }
  };

  Node<T> *head;
  int Size;
};
}  // namespace s21

#include "s21_stack.tpp"

#endif  // CPP2_S21_CONTAINERS_S21_STACK_H_