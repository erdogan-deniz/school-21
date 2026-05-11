/**
 * @file s21_vector.h
 * @brief `s21::vector<T>` — dynamic contiguous-storage array, STL
 *        `std::vector` parallel.
 *
 * Mirrors the public API of `std::vector<T>` (modulo the
 * SCREAMING_SNAKE / `noexcept` polish): default + sized + initialiser
 * list + copy + move ctors, element access (`at` / `operator[]` /
 * `front` / `back` / `data`), iterators, capacity (`empty` / `size` /
 * `max_size` / `capacity` / `reserve` / `shrink_to_fit`), modifiers
 * (`clear` / `insert` / `erase` / `push_back` / `pop_back` / `swap`).
 *
 * Iterators are implemented as wrapper types (@ref VectorIterator,
 * @ref VectorConstIterator) around a raw `T*`, with implicit
 * conversion `VectorIterator → VectorConstIterator`.
 *
 * Method definitions live in `s21_vector.tpp` (included at the bottom
 * of this header).
 */

#ifndef VECTOR_H
#define VECTOR_H
#include <cmath>

using namespace std;

namespace s21 {

template <class T>
class VectorIterator;

template <class T>
class VectorConstIterator;

/**
 * @brief STL-parallel `vector<T>` — owns a contiguous heap buffer
 *        whose capacity grows geometrically on `push_back` overflow.
 */
template <class T>
class vector {
 public:
  // Vector Member type
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = VectorIterator<T>;
  using const_iterator = VectorConstIterator<T>;
  using size_type = std::size_t;
  using pointer = T *;

 public:
  /// @name Member functions — construction / destruction / assignment
  /// @{
  vector();                                                ///< Default ctor — empty, capacity 0.
  vector(size_type n);                                     ///< Construct with @p n default-initialised elements.
  vector(std::initializer_list<value_type> const &items);  ///< Brace-list ctor.
  vector(const vector &v);                                 ///< Copy ctor.
  vector(vector &&v);                                      ///< Move ctor.
  ~vector();                                               ///< Releases the heap buffer.
  vector &operator=(vector &&v);                           ///< Move assignment.
  /// @}

  /// @name Element access
  /// @{
  reference at(size_type pos);              ///< Bounds-checked access; throws on out-of-range.
  reference operator[](size_type pos);      ///< Unchecked access.
  const_reference front();                  ///< First element (UB if empty).
  const_reference back();                   ///< Last element (UB if empty).
  pointer data();                           ///< Raw pointer to the underlying buffer.
  /// @}

  /// @name Iterators
  /// @{
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
  /// @}

  /// @name Capacity
  /// @{
  bool empty() const;                       ///< True iff size == 0.
  size_type size() const;                   ///< Number of elements currently stored.
  size_type max_size() const;               ///< Implementation-defined upper bound.
  size_type capacity() const;               ///< Allocated buffer size in elements.
  void reserve(size_type size);             ///< Grow the buffer to at least @p size.
  void shrink_to_fit();                     ///< Trim capacity down to size.
  /// @}

  /// @name Modifiers
  /// @{
  void clear();                                          ///< Drop every element (capacity preserved).
  iterator insert(iterator pos, const_reference value);  ///< Insert before @p pos.
  void erase(iterator pos);                              ///< Remove element at @p pos.
  void push_back(const_reference value);                 ///< Append at the back.
  void pop_back();                                       ///< Drop the back element.
  void swap(vector &other);                              ///< O(1) swap with @p other.
  /// @}

 private:
  size_type size_;
  size_type capacity_;
  value_type *container_;

  // helper
  void bring_to_zero();
  void add_memory(size_type size, bool flag);
  size_type add_memory_size(size_type size, bool flag);
  void copy_vector(const vector &v);
  void remove();
};

/**
 * @brief Mutable random-access iterator over @ref vector.
 *
 * Lightweight wrapper around a raw `T*`. Supports `*`, `->`, prefix
 * and postfix `++` / `--`, arithmetic `+` / `-` with `size_t`, and
 * `==` / `!=` against another @ref VectorIterator. Implicitly
 * convertible to @ref VectorConstIterator.
 */
template <class T>
class VectorIterator {
  friend class vector<T>;
  friend class VectorConstIterator<T>;

  using value_type = T;
  using pointer = T *;
  using reference = T &;

 public:
  VectorIterator() { ptr_ = nullptr; }
  VectorIterator(pointer ptr) { ptr_ = ptr; }

  value_type &operator*() const { return (*ptr_); }
  pointer operator->() { return ptr_; }

  VectorIterator &operator++() {
    ptr_++;
    return *this;
  }

  VectorIterator &operator--() {
    ptr_--;
    return *this;
  }

  VectorIterator operator++(int) {
    VectorIterator tmp = *this;
    ++(*this);
    return tmp;
  }

  VectorIterator operator--(int) {
    VectorIterator tmp = *this;
    --(*this);
    return tmp;
  }

  VectorIterator operator+(const size_t value) {
    VectorIterator tmp(this->ptr_ + value);
    return tmp;
  }

  VectorIterator operator-(const size_t value) {
    VectorIterator tmp(this->ptr_ - value);
    return tmp;
  }

  bool operator==(const VectorIterator &other) { return ptr_ == other.ptr_; }

  bool operator!=(const VectorIterator &other) { return ptr_ != other.ptr_; }

  operator VectorConstIterator<T>() const {
    return VectorConstIterator<T>(ptr_);
  }

 private:
  pointer ptr_;
};

/**
 * @brief Read-only random-access iterator over @ref vector.
 *
 * Same shape as @ref VectorIterator but `operator*` returns by value
 * (preserving const-correctness in const-context use). Implicitly
 * convertible to @ref VectorIterator for round-trip mutation paths.
 */
template <class T>
class VectorConstIterator {
  friend class vector<T>;
  friend class VectorIterator<T>;

  using value_type = T;
  using pointer = T *;
  using reference = T &;

 public:
  VectorConstIterator() { ptr_ = nullptr; };
  VectorConstIterator(pointer ptr) { ptr_ = ptr; };
  value_type operator*() const { return (*ptr_); }
  pointer operator->() { return ptr_; }

  VectorConstIterator &operator++() {
    ptr_++;
    return *this;
  }

  VectorConstIterator &operator--() {
    ptr_--;
    return *this;
  }

  VectorConstIterator operator++(int) {
    VectorConstIterator tmp = *this;
    ++(*this);
    return tmp;
  }

  VectorConstIterator operator--(int) {
    VectorConstIterator tmp = *this;
    --(*this);
    return tmp;
  }

  bool operator==(const VectorConstIterator &other) {
    return ptr_ == other.ptr_;
  }

  bool operator!=(const VectorConstIterator &other) {
    return ptr_ != other.ptr_;
  }

  operator VectorIterator<T>() const { return VectorIterator<T>(ptr_); }

 private:
  pointer ptr_;
};

}  // namespace s21

#include "s21_vector.tpp"

#endif  // VECTOR_H