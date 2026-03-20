#include "../../s21_containers.h"

template <typename T>
s21::Queue<T>::Queue() {
  this->Size = 0;
  this->head = nullptr;
  this->tail = nullptr;
}

template <typename T>
s21::Queue<T>::Queue(const Queue &q) {
  this->head = nullptr;
  this->tail = nullptr;
  this->Size = q.Size;
  this->head = new Node<T>(q.head->data);
  Node<T> *tmpPtrThis = this->head;
  Node<T> *tmpPtrOther = q.head;
  Node<T> *tmpPrev;

  for (int i = 0; i < this->Size; i++) {
    tmpPtrThis->data = tmpPtrOther->data;
    if (i == q.Size - 1) break;
    tmpPrev = tmpPtrThis;
    tmpPtrThis->ptrNext = new Node<T>();
    tmpPtrThis = tmpPtrThis->ptrNext;
    tmpPtrThis->ptrPrev = tmpPrev;
    tmpPtrOther = tmpPtrOther->ptrNext;
    if (q.Size - 2 != i) {
      tmpPrev = nullptr;
      delete tmpPrev;
    }
  }

  tmpPtrThis->ptrPrev = tmpPrev;

  Node<T> *tmpTail = this->head;

  for (int i = 0; i < this->Size - 1; i++) {
    tmpTail = tmpTail->ptrNext;
  }

  this->tail = tmpTail;
}

template <typename T>
s21::Queue<T>::Queue(Queue &&q) {
  this->Size = q.Size;
  this->head = q.head;
  this->tail = q.tail;

  q.Size = 0;
  q.head = nullptr;
  q.tail = nullptr;
}

template <typename T>
void s21::Queue<T>::operator=(Queue &q) {
  if (this->head != nullptr) this->~Queue();
  Queue<T> tmpQueue(q);

  this->Size = tmpQueue.Size;
  this->head = tmpQueue.head;
  this->tail = tmpQueue.tail;

  tmpQueue.Size = 0;
  tmpQueue.head = nullptr;
  tmpQueue.tail = nullptr;
}

template <typename T>
s21::Queue<T>::~Queue() {
  int count = this->Size;
  this->Size = 0;

  for (int i = 0; i < count; i++) {
    Node<T> *tmpPtr = this->head;
    this->head = this->head->ptrNext;
    delete tmpPtr;
  }

  this->tail = nullptr;
}

template <typename T>
void s21::Queue<T>::push(const_reference value) {
  Node<T> *tmpPtr = new Node<T>(value);
  tmpPtr->ptrNext = head;

  if (head != nullptr) head->ptrPrev = tmpPtr;
  if (tail == nullptr) tail = tmpPtr;
  head = tmpPtr;
  Size++;
}

template <typename T>
void s21::Queue<T>::pop() {
  try {
    if (tail == nullptr) throw "Error: Queue is empty";
  } catch (const char *e) {
    std::cerr << e << '\n';
    exit(1);
  }

  Node<T> *tmpPtr = this->tail;
  this->tail = this->tail->ptrPrev;
  if (tail != nullptr) this->tail->ptrNext = nullptr;
  delete tmpPtr;
  Size--;
}

template <typename T>
typename s21::Queue<T>::const_reference s21::Queue<T>::front() {
  try {
    if (!Size) throw "Error: There are no elements on the queue";
  } catch (const char *e) {
    std::cerr << e << '\n';
    exit(1);
  }

  return this->tail->data;
}

template <typename T>
typename s21::Queue<T>::const_reference s21::Queue<T>::back() {
  try {
    if (!Size) throw "Error: There are no elements on the queue";
  } catch (const char *e) {
    std::cerr << e << '\n';
    exit(1);
  }

  return this->head->data;
}

template <typename T>
void s21::Queue<T>::swap(s21::Queue<T> &other) {
  Queue<T> tmpPtr(other);
  other.Size = this->Size;
  other.head = this->head;
  other.tail = this->tail;
  this->Size = tmpPtr.Size;
  this->head = tmpPtr.head;
  this->tail = tmpPtr.tail;

  tmpPtr.Size = 0;
  tmpPtr.head = nullptr;
  tmpPtr.tail = nullptr;
}