/**
 * @file s21_array.h
 * @brief `s21::array<T, N>` — fixed-size compile-time array, STL
 *        `std::array` parallel.
 *
 * The size `N` is a template parameter, so storage is inline (no heap
 * allocation). Iterators are raw `T*` / `const T*`. Suitable for
 * small constant-sized containers where the size is known at compile
 * time and `std::vector`'s heap overhead would be wasteful.
 */

#ifndef S21_CONTAINERS_SRC_S21_ARRAY_H_
#define S21_CONTAINERS_SRC_S21_ARRAY_H_

namespace s21 {
/**
 * @brief STL-parallel `array<T, N>` — fixed-size, stack-allocated.
 *
 * No reallocation, no resize. `at` throws on bounds violation;
 * `operator[]` does not. `data()` returns a non-const pointer even
 * in const context — kept for STL parity though strict const-
 * correctness would prefer `const T*`.
 */
template <typename T, size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  /// @name Construction / destruction / assignment
  /// @{
  array() = default;  ///< Default ctor — elements default-initialised.

  /** @brief Brace-list ctor. @p items size must be ≤ N. */
  array(std::initializer_list<value_type> const &items) {
    std::copy(items.begin(), items.end(), arr);
  }

  /** @brief Element-wise copy ctor. */
  array(const array &a) {
    for (size_type i = 0; i < a.size(); ++i) arr[i] = a.arr[i];
  }

  /** @brief Element-wise move ctor. */
  array(array &&a) {
    for (size_type i = 0; i < a.size(); ++i) arr[i] = std::move(a.arr[i]);
  }

  ~array() = default;

  /** @brief Move assignment — block-move every element. */
  array &operator=(array &&a) {
    std::move(a.arr, a.arr + N, arr);
    return *this;
  }
  /// @}

  /// @name Element access
  /// @{

  inline reference at(size_type pos) {
    if (pos >= N) throw std::out_of_range("array::at");

    return arr[pos];
  }

  inline reference operator[](size_type pos) noexcept { return arr[pos]; }

  inline const_reference front() const noexcept { return arr[0]; }

  inline const_reference back() const noexcept { return arr[N - 1]; }

  inline iterator data() const noexcept { return arr; }  ///< Raw pointer to storage.
  /// @}

  /// @name Iterators
  /// @{
  inline iterator begin() noexcept { return arr; }
  inline iterator end() noexcept { return arr + N; }
  /// @}

  /// @name Capacity
  /// @{
  inline bool empty() const noexcept { return size() == 0; }  ///< True iff `N == 0`.
  inline size_type size() const noexcept { return N; }        ///< Always `N`.
  inline size_type max_size() const noexcept { return N; }    ///< Same as @ref size — fixed-size.
  /// @}

  /// @name Operations
  /// @{
  /** @brief Pair-wise element swap with @p other (O(N)). */
  inline void swap(array &other) { std::swap_ranges(arr, arr + N, other.arr); }

  /** @brief Set every element to @p value. */
  inline void fill(const_reference value) {
    for (size_t i = 0; i < N; ++i) arr[i] = value;
  }
  /// @}

 private:
  value_type arr[N];
};
}  // namespace s21

#endif  // S21_CONTAINERS_SRC_S21_ARRAY_H_
