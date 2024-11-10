#include "../../s21_containers.h"

template <typename T>
s21::Stack<T>::Stack() {
  Size = 0;
  head = nullptr;
}

template <typename T>
s21::Stack<T>::Stack(const Stack &s) {
  this->Size = s.Size;
  this->head = new Node<T>(s.head->data);
  Node<T> *tmpPtrThis = this->head;
  Node<T> *tmpPtrOther = s.head;

  for (int i = 0; i < s.Size; i++) {
    tmpPtrThis->data = tmpPtrOther->data;
    if (i == s.Size - 1) break;
    tmpPtrThis->ptrNext = new Node<T>();
    tmpPtrThis = tmpPtrThis->ptrNext;
    tmpPtrOther = tmpPtrOther->ptrNext;
  }

  tmpPtrThis = nullptr;
}

template <typename T>
s21::Stack<T>::Stack(Stack &&s) {
  this->Size = s.Size;
  this->head = s.head;
  s.Size = 0;
  s.head = nullptr;
}

template <typename T>
s21::Stack<T>::~Stack() {
  int count = this->Size;
  this->Size = 0;

  for (int i = 0; i < count; i++) {
    Node<T> *tmpPtr = this->head;
    this->head = this->head->ptrNext;
    delete tmpPtr;
  }
}

template <typename T>
void s21::Stack<T>::operator=(Stack &s) {
  if (this->head != nullptr) this->~Stack();
  Stack<T> tmpStack(s);

  this->Size = tmpStack.Size;
  this->head = tmpStack.head;

  tmpStack.Size = 0;
  tmpStack.head = nullptr;
}

template <typename T>
void s21::Stack<T>::push(const_reference value) {
  if (this->head == nullptr)
    this->head = new Node<T>(value);
  else {
    Node<T> *tmpPtr = new Node<T>(value);
    tmpPtr->ptrNext = this->head;
    this->head = tmpPtr;
  }

  Size++;
}

template <typename T>
void s21::Stack<T>::pop() {
  try {
    if (this->head == nullptr) throw "There are no elements on the stack";
  } catch (const char *e) {
    std::cerr << e << '\n';
    exit(1);
  }

  Node<T> *tmpPtr = this->head;
  this->head = this->head->ptrNext;
  delete tmpPtr;
  Size--;
}

template <typename T>
typename s21::Stack<T>::const_reference s21::Stack<T>::top() {
  try {
    if (this->head == nullptr) throw "There are no elements on the stack";
  } catch (const char *e) {
    std::cerr << e << '\n';
    exit(1);
  }

  return this->head->data;
}

template <typename T>
void s21::Stack<T>::swap(s21::Stack<T> &other) {
  Stack<T> tmpPtr(other);
  other.Size = this->Size;
  other.head = this->head;
  this->Size = tmpPtr.Size;
  this->head = tmpPtr.head;

  tmpPtr.Size = 0;
  tmpPtr.head = nullptr;
}