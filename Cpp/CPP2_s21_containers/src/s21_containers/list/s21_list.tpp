#include "../../s21_containers.h"

template <typename T>
s21::List<T>::List() {
  this->Size = 0;
  this->head = nullptr;
  this->tail = nullptr;
  this->iter = nullptr;
}

template <typename T>
s21::List<T>::List(size_type n) {
  this->Size = n;
  this->head = nullptr;
  this->tail = nullptr;

  for (int i = 0; i < n; i++) {
    Node<T> *tmpPtr = new Node<T>;
    tmpPtr->ptrPrev = this->tail;

    if (this->tail != nullptr) this->tail->ptrNext = tmpPtr;
    if (this->head == nullptr) this->head = tmpPtr;
    this->tail = tmpPtr;
  }
}

template <typename T>
s21::List<T>::List(const List &l) {
  this->Size = l.Size;
  this->head = new Node<T>(l.head->data);
  Node<T> *tmpThis = this->head;
  Node<T> *tmpOther = l.head;

  for (int i = 0; i < l.Size - 1; i++) {
    Node<T> *tmpPtr = tmpThis;
    tmpOther = tmpOther->ptrNext;
    tmpThis->ptrNext = new Node<T>(tmpOther->data);
    tmpThis = tmpThis->ptrNext;
    tmpThis->ptrPrev = tmpPtr;
    this->tail = tmpThis;
  }
}

template <typename T>
s21::List<T>::List(List &&l) {
  this->Size = l.Size;
  this->head = l.head;
  this->tail = l.tail;

  l.Size = 0;
  l.head = nullptr;
  l.tail = nullptr;
}

template <typename T>
s21::List<T>::~List() {
  int count = this->Size;
  this->Size = 0;

  for (int i = 0; i < count; i++) {
    Node<T> *tmpPtr = this->head;
    this->head = this->head->ptrNext;
    delete tmpPtr;
  }

  this->tail = nullptr;
  if (this->iter) this->iter->ptrIter = nullptr;
  this->iter = nullptr;
}

template <typename T>
typename s21::List<T>::const_reference s21::List<T>::front() {
  try {
    if (!Size) throw "Error: There are no elements on the queue";
  } catch (const char *e) {
    std::cerr << e << '\n';
    exit(1);
  }

  return this->head->data;
}

template <typename T>
typename s21::List<T>::const_reference s21::List<T>::back() {
  try {
    if (!Size) throw "Error: There are no elements on the queue";
  } catch (const char *e) {
    std::cerr << e << '\n';
    exit(1);
  }

  return this->tail->data;
}

template <typename T>
void s21::List<T>::push_front(const_reference value) {
  Node<T> *tmpPtr = new Node<T>(value);
  tmpPtr->ptrNext = this->head;

  if (this->head != nullptr) this->head->ptrPrev = tmpPtr;
  if (this->tail == nullptr) this->tail = tmpPtr;
  this->head = tmpPtr;
  this->Size++;
}

template <typename T>
void s21::List<T>::pop_front() {
  try {
    if (tail == nullptr) throw "Error: Queue is empty";
  } catch (const char *e) {
    std::cerr << e << '\n';
    exit(1);
  }

  Node<T> *tmpPtr = this->head;
  this->head = this->head->ptrNext;
  if (this->head != nullptr)
    this->head->ptrPrev = nullptr;
  else
    this->tail = nullptr;
  delete tmpPtr;
  this->Size--;
}

template <typename T>
void s21::List<T>::push_back(const_reference value) {
  Node<T> *tmpTail = this->tail;
  Node<T> *tmpPtr = new Node<T>(value);

  if (this->tail == nullptr) {
    this->head = tmpPtr;
    this->tail = tmpPtr;
  } else {
    this->tail->ptrNext = tmpPtr;
    this->tail = this->tail->ptrNext;
    this->tail->ptrPrev = tmpTail;
  }

  this->Size++;
}

template <typename T>
void s21::List<T>::pop_back() {
  try {
    if (tail == nullptr) throw "Error: Queue is empty";
  } catch (const char *e) {
    std::cerr << e << '\n';
    exit(1);
  }

  Node<T> *tmpPtr = this->tail;
  this->tail = this->tail->ptrPrev;
  if (this->tail != nullptr)
    this->tail->ptrNext = nullptr;
  else
    this->head = nullptr;
  delete tmpPtr;
  this->Size--;
}

template <typename T>
T &s21::List<T>::operator[](const int index) {
  try {
    if (index >= this->Size || index < 0) throw "Out of list";
  } catch (const char *e) {
    std::cerr << e << '\n';
    exit(1);
  }

  Node<T> *tmpPtr = this->head;

  for (int i = 0; i < index; i++) {
    tmpPtr = tmpPtr->ptrNext;
  }

  return tmpPtr->data;
}

template <typename T>
void s21::List<T>::clear() {
  int count = this->Size;
  for (int i = 0; i < count; i++) pop_back();
}

template <typename T>
void s21::List<T>::operator=(List &l) {
  if (this->head != nullptr) this->~List();
  s21::List<T> tmpList(l);

  this->Size = tmpList.Size;
  this->head = tmpList.head;
  this->tail = tmpList.tail;

  tmpList.Size = 0;
  tmpList.head = nullptr;
  tmpList.tail = nullptr;
}

template <typename T>
void s21::List<T>::swap(s21::List<T> &other) {
  s21::List<T> tmpList(other);
  other.Size = this->Size;
  other.head = this->head;
  other.tail = this->tail;

  this->Size = tmpList.Size;
  this->head = tmpList.head;
  this->tail = tmpList.tail;

  tmpList.Size = 0;
  tmpList.head = nullptr;
  tmpList.tail = nullptr;
}

template <typename T>
void s21::List<T>::reverse() {
  Node<T> *tmpHead = this->head;
  Node<T> *tmpTail = this->tail;

  for (int i = 0; i < this->Size / 2; i++) {
    T tmpData = tmpHead->data;
    tmpHead->data = tmpTail->data;
    tmpTail->data = tmpData;
    tmpHead = tmpHead->ptrNext;
    tmpTail = tmpTail->ptrPrev;
  }
}

template <typename T>
void s21::List<T>::sort() {
  for (int i = 0; i < this->Size - 1; i++) {
    for (int j = 0; j < this->Size - 1 - i; j++) {
      if ((*this)[j] > (*this)[j + 1]) {
        T tmpData = (*this)[j];
        (*this)[j] = (*this)[j + 1];
        (*this)[j + 1] = tmpData;
      }
    }
  }
}

template <typename T>
void s21::List<T>::erase(iterator pos) {
  Node<T> *tmpPtrRun = this->head;
  Node<T> *tmpPtrDel = this->head;

  if (pos.check_last())
    pop_back();
  else if (pos.check_firts())
    pop_front();
  else {
    pos--;

    for (s21::List<T>::iterator tmp = this->begin(); tmp != pos; tmp++) {
      tmpPtrRun = tmpPtrRun->ptrNext;
      tmpPtrDel = tmpPtrDel->ptrNext;
    }

    tmpPtrDel = tmpPtrDel->ptrNext;
    tmpPtrRun->ptrNext = tmpPtrDel->ptrNext;
    tmpPtrRun->ptrNext->ptrPrev = tmpPtrRun;
    delete tmpPtrDel;
    this->iter->ptrIter = tmpPtrRun;
    this->Size--;
  }
}

template <typename T>
void s21::List<T>::unique() {
  try {
    if (!Size) throw "Error: List is empty";
  } catch (const char *e) {
    std::cerr << e << '\n';
    exit(1);
  }

  if (Size > 1) {
    s21::List<T>::iterator it1;
    s21::List<T>::iterator it2;
    it1 = it2 = this->begin();
    it2++;
    int count = this->Size;

    for (int i = 0; i < count - 1; i++) {
      if (*it1 == *it2) {
        s21::List<T>::iterator itTmp = it1;
        if (i == count - 2) {
          erase(itTmp);
          break;
        }
        it1++;
        it2++;
        erase(itTmp);
      } else {
        if (i == count - 2) break;
        it1++;
        it2++;
      }
    }
  }
}

template <typename T>
void s21::List<T>::merge(s21::List<T> &other) {
  for (int i = 0; i < other.Size; i++) this->push_back(other[i]);
  this->sort();
  other.~List();
}

template <typename T>
typename s21::List<T>::iterator s21::List<T>::begin() {
  ListIterator<T> *tmpPtr = new ListIterator<T>;
  tmpPtr->ptrIter = new Node<T>;
  tmpPtr->ptrIter = this->head;

  this->iter = tmpPtr;
  return *this->iter;
}

template <typename T>
typename s21::List<T>::iterator s21::List<T>::end() {
  ListIterator<T> *tmpPtr = new ListIterator<T>;
  tmpPtr->ptrIter = new Node<T>;
  this->tail->ptrNext = new Node<T>;
  this->tail->ptrNext->ptrPrev = this->tail;
  tmpPtr->ptrIter = this->tail->ptrNext;
  this->iter = tmpPtr;
  return *this->iter;
}

template <typename T>
typename s21::List<T>::iterator s21::List<T>::insert(iterator pos,
                                                     const_reference value) {
  if (pos.check_firts()) {
    push_front(value);
    pos = this->begin();
  } else if (pos.check_last()) {
    push_back(value);
    pos = this->end();
    pos--;
  } else {
    Node<T> *tmpPtr = pos.ptrIter;
    pos.ptrIter = new Node<T>(value);
    pos.ptrIter->ptrPrev = tmpPtr->ptrPrev;
    tmpPtr->ptrPrev = pos.ptrIter;
    pos.ptrIter->ptrNext = tmpPtr;
    pos.ptrIter->ptrPrev->ptrNext = pos.ptrIter;
    this->Size++;
  }

  return pos;
}

template <typename T>
void s21::List<T>::splice(const_iterator pos, s21::List<T> &other) {
  std::cout << 123 << std::endl;
}
