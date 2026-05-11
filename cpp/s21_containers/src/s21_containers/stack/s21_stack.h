/**
 * @file s21_stack.h
 * @brief `s21::Stack<T>` — LIFO container adapter, STL `std::stack`
 *        parallel.
 *
 * Internally backed by a singly-linked chain of `Node`s rooted at
 * `head`. `push` prepends to the head, `pop` removes from the head,
 * `top` peeks at it. All three are O(1). Method definitions live in
 * `s21_stack.tpp`.
 */

#ifndef CPP2_S21_CONTAINERS_S21_STACK_H_
#define CPP2_S21_CONTAINERS_S21_STACK_H_

namespace s21 {
/**
 * @brief STL-parallel LIFO adapter over a custom singly-linked list.
 */
template <typename T>
class Stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  /// @name Construction / destruction
  /// @{
  Stack();                    ///< Default ctor — empty stack.
  Stack(const Stack &s);      ///< Copy ctor — deep-copies every node.
  Stack(Stack &&s);           ///< Move ctor.
  ~Stack();                   ///< Releases every node.
  void operator=(Stack &s);   ///< Copy assignment.
  /// @}

  /// @name Element access
  /// @{
  const_reference top();      ///< Peek at the head (next to `pop`).
  /// @}

  /// @name Capacity
  /// @{
  size_type size() { return this->Size; }
  bool empty() { return this->size() ? 0 : 1; }
  /// @}

  /// @name Modifiers
  /// @{
  void push(const_reference value);  ///< Push on top.
  void pop();                        ///< Pop the top.
  void swap(Stack<T> &other);        ///< O(1) swap with @p other.
  /// @}

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