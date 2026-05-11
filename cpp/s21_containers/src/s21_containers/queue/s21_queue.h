/**
 * @file s21_queue.h
 * @brief `s21::Queue<T>` — FIFO container adapter, STL `std::queue`
 *        parallel.
 *
 * Internally backed by an owned doubly-linked list of `Node`s with
 * head/tail pointers; `push` appends at the tail, `pop` removes from
 * the head. `front` / `back` peek at the two ends. Method definitions
 * live in `s21_queue.tpp`.
 */

#ifndef CPP2_S21_CONTAINERS_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_S21_QUEUE_H_

namespace s21 {
/**
 * @brief STL-parallel FIFO adapter over a custom doubly-linked list.
 */
template <typename T>
class Queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  /// @name Construction / destruction
  /// @{
  Queue();                    ///< Default ctor — empty queue.
  Queue(const Queue &q);      ///< Copy ctor — deep-copies every node.
  Queue(Queue &&q);           ///< Move ctor.
  void operator=(Queue &q);   ///< Copy assignment.
  ~Queue();                   ///< Releases every node.
  /// @}

  /// @name Element access
  /// @{
  const_reference front();    ///< Peek at the head (next to `pop`).
  const_reference back();     ///< Peek at the tail (last pushed).
  /// @}

  /// @name Capacity
  /// @{
  bool empty() { return this->size() > 0 ? 0 : 1; }
  size_type size() { return this->Size; }
  /// @}

  /// @name Modifiers
  /// @{
  void push(const_reference value);  ///< Enqueue at the tail.
  void pop();                        ///< Dequeue from the head.
  void swap(Queue<T> &other);        ///< O(1) swap with @p other.
  /// @}

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