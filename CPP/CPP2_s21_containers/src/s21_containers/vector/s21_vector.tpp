#include "../../s21_containers.h"
#include "s21_vector.h"

namespace s21 {
// Vector Member functions
template <class value_type>
vector<value_type>::vector() {
  this->bring_to_zero();
}

template <class value_type>
vector<value_type>::vector(size_type n) {
  if (this->max_size() < n) {
    throw std::out_of_range("cannot create s21::vector larger than max_size()");
  }
  this->size_ = n;
  this->capacity_ = n;
  this->container_ = new value_type[n];
}

template <class value_type>
vector<value_type>::vector(std::initializer_list<value_type> const& items) {
  this->capacity_ = this->size_ = items.size();
  if (this->size_) {
    this->container_ = new value_type[this->size_];
    std::copy(items.begin(), items.end(), this->container_);
  } else {
    this->bring_to_zero();
  }
}

template <class value_type>
vector<value_type>::vector(const vector& v) {
  this->copy_vector(v);
}

template <class value_type>
vector<value_type>::vector(vector&& v) {
  this->size_ = v.size_;
  this->capacity_ = v.capacity_;
  this->container_ = v.container_;
  v.bring_to_zero();
}

template <class value_type>
vector<value_type>::~vector() {
  this->remove();
}

template <class value_type>
typename s21::vector<value_type>& vector<value_type>::operator=(vector&& v) {
  if (this != &v) {
    this->remove();
    this->size_ = v.size_;
    this->capacity_ = v.capacity_;
    this->container_ = v.container_;
    v.bring_to_zero();
  }
  return *this;
}

// Vector Element access
template <class value_type>
typename vector<value_type>::reference vector<value_type>::at(size_type pos) {
  if (pos >= this->size_) {
    throw std::out_of_range("Index out of range");
  }
  return this->container_[pos];
}

template <class value_type>
typename vector<value_type>::reference vector<value_type>::operator[](
    size_type pos) {
  size_type less_zero = 0;
  if (this->size() < pos || less_zero > pos) {
    throw std::out_of_range("Index out of range");
  }
  return container_[pos];
}

template <class value_type>
typename vector<value_type>::const_reference vector<value_type>::front() {
  if (this->empty()) {
    throw std::out_of_range("Out of range");
  }
  return *container_;
}

template <class value_type>
typename vector<value_type>::const_reference vector<value_type>::back() {
  if (this->empty()) {
    throw std::out_of_range("Out of range");
  }
  return *(container_ + size_ - 1);
}

template <class value_type>
typename vector<value_type>::pointer vector<value_type>::data() {
  return container_;
}

// Vector Iterators
template <class value_type>
typename vector<value_type>::iterator vector<value_type>::begin() {
  return iterator(container_);
}

template <class value_type>
typename vector<value_type>::iterator vector<value_type>::end() {
  return iterator(container_ + size_);
}

template <class value_type>
typename vector<value_type>::const_iterator vector<value_type>::begin() const {
  return const_iterator(container_);
}

template <class value_type>
typename vector<value_type>::const_iterator vector<value_type>::end() const {
  return const_iterator(container_ + size_);
}

// Vector Capacity
template <class value_type>
bool vector<value_type>::empty() const {
  return size_ == 0;
}

template <class value_type>
typename vector<value_type>::size_type vector<value_type>::size() const {
  return size_;
}

template <class value_type>
typename vector<value_type>::size_type vector<value_type>::max_size() const {
  char bits = 63;
  if (sizeof(void*) == 4) {
    bits = 31;
  }
  return static_cast<size_type>(pow(2, bits)) / sizeof(value_type) - 1;
}

template <class value_type>
typename vector<value_type>::size_type vector<value_type>::capacity() const {
  return capacity_;
}

template <class value_type>
void vector<value_type>::reserve(size_type size) {
  size_type less_zero = 0;
  if (less_zero > size) {
    throw std::out_of_range("Index out of range");
  }
  if (size > this->size_) {
    this->add_memory(size, true);
  }
}

template <class value_type>
void vector<value_type>::shrink_to_fit() {
  if (this->size_ < this->capacity_) {
    this->add_memory(this->size_, true);
  }
}

// Vector Modifiers
template <class value_type>
void vector<value_type>::clear() {
  this->size_ = 0;
}

template <class value_type>
typename vector<value_type>::iterator vector<value_type>::insert(
    iterator pos, const_reference value) {
  size_type position = &(*pos) - this->container_;
  size_type zero = 0;
  if (zero > position || position > this->size_) {
    throw std::out_of_range("Index out ot range");
  }
  if (this->size_ + 1 >= this->capacity_) {
    this->add_memory(this->capacity_ * 2, true);
  }
  value_type replace = this->container_[position];
  this->size_++;
  this->container_[position] = value;
  for (size_type i = position + 1; i < this->size_; ++i) {
    value_type next = this->container_[i];
    this->container_[i] = replace;
    replace = next;
  }
  return this->container_ + position;
}

template <class value_type>
void vector<value_type>::erase(iterator pos) {
  size_type position = &(*pos) - this->container_;
  size_type zero = 0;
  if (zero > position || position > this->size_) {
    throw std::out_of_range("Index out ot range");
  }
  for (size_type i = position + 1; i < this->size_; i++) {
    this->container_[i - 1] = this->container_[i];
  }
  this->size_--;
}

template <class value_type>
void vector<value_type>::push_back(const_reference value) {
  if (this->size_ >= this->capacity_) {
    add_memory(0, false);
  }
  this->container_[this->size_++] = value;
}

template <class value_type>
void vector<value_type>::pop_back() {
  this->size_ > 0 ? this->size_-- : 0;
}

template <class value_type>
void vector<value_type>::swap(vector& other) {
  std::swap(other.size_, this->size_);
  std::swap(other.capacity_, this->capacity_);
  std::swap(other.container_, this->container_);
}

// Helpers
template <class value_type>
void vector<value_type>::copy_vector(const vector& v) {
  this->size_ = v.size_;
  this->capacity_ = v.capacity_;
  this->container_ = new value_type[this->size_];
  for (size_type i = 0; i < this->size_; i++) {
    this->container_[i] = v.container_[i];
  }
}

template <class value_type>
void vector<value_type>::add_memory(size_type size, bool flag) {
  this->capacity_ = this->add_memory_size(size, flag);
  value_type* tmp = this->container_;
  this->container_ = new value_type[this->capacity_];
  for (size_t i = 0; i < this->size_; ++i) {
    this->container_[i] = tmp[i];
  }
  delete[] tmp;
}

template <class value_type>
typename vector<value_type>::size_type vector<value_type>::add_memory_size(
    size_type size, bool flag) {
  size_type n = 2;
  return flag ? size : n * (this->capacity_ > 0 ? this->capacity_ : n);
}

template <class value_type>
void vector<value_type>::bring_to_zero() {
  this->size_ = 0;
  this->capacity_ = 0;
  this->container_ = nullptr;
}

template <class value_type>
void vector<value_type>::remove() {
  if (this->container_) {
    delete[] this->container_;
  }
  this->container_ = nullptr;
  this->size_ = this->capacity_ = 0;
}
}  // namespace s21