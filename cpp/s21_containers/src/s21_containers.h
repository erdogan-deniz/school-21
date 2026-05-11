/**
 * @file s21_containers.h
 * @brief Umbrella header for the `s21::` STL replica.
 *
 * Includes every container in the library. Drop this single header into
 * any C++17 translation unit and use the types via the `s21::` namespace:
 *
 * ```cpp
 * #include "s21_containers.h"
 *
 * s21::vector<int> v{1, 2, 3};
 * s21::map<std::string, int> m;
 * s21::list<double> l;
 * ```
 *
 * Each individual container header is also independently includable:
 * `s21_containers/vector/s21_vector.h`, etc.
 *
 * Containers provided:
 * - **Sequence:** `s21::list`, `s21::vector`, `s21::array`, `s21::stack`,
 *   `s21::queue`.
 * - **Associative:** `s21::map`, `s21::set`, `s21::multiset`.
 *
 * The shape and semantics mirror the standard library (`std::list`,
 * `std::vector`, ...) with the same iterator categories. Implementations
 * are not derived from libstdc++ / libc++ sources.
 *
 * @copyright MIT for the repository as a whole; the School 21
 *            placeholder licence file inside this subproject is
 *            preserved as educational attribution.
 */

#ifndef CPP2_S21_CONTAINERS_H_
#define CPP2_S21_CONTAINERS_H_

#include <cstddef>
#include <iostream>

#include "gtest/gtest.h"
#include "s21_containers/array/s21_array.h"
#include "s21_containers/list/s21_list.h"
#include "s21_containers/map/s21_map.h"
#include "s21_containers/multiset/s21_multiset.h"
#include "s21_containers/queue/s21_queue.h"
#include "s21_containers/set/s21_set.h"
#include "s21_containers/stack/s21_stack.h"
#include "s21_containers/vector/s21_vector.h"

#endif  // CPP2_S21_CONTAINERS_H_
