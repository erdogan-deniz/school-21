#ifndef CPP2_S21_CONTAINERS_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_S21_QUEUE_H_

namespace s21 {
template <typename T>
class Queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  Queue();
  Queue(const Queue &q);
  Queue(Queue &&q);
  void operator=(Queue &q);
  ~Queue();

  const_reference front();
  const_reference back();

  bool empty() { return this->size() > 0 ? 0 : 1; }
  size_type size() { return this->Size; }

  void push(const_reference value);
  void pop();
  void swap(Queue<T> &other);

 private:
  template <typename>
  class Node {
   public:
    T data;
    Node *ptrNext;
    Node *ptrPrev;

    Node(T data = T(), Node *ptrNext = nullptr, Node *ptrPrev = nullptr) {
      this->data = data;
      this->ptrNext = ptrNext;
      this->ptrPrev = ptrPrev;
    }
  };

  int Size;
  Node<T> *head;
  Node<T> *tail;
};
}  // namespace s21

#include "s21_queue.tpp"

#endif  // CPP2_S21_CONTAINERS_S21_QUEUE_H_