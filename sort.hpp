#ifndef SORT_HPP_
#define SORT_HPP_

#include <algorithm>
#include <cmath>
#include <iostream>
#include <thread>
#include <vector>

#define VEC_SIZE 100

// =============== Custom merge ==================== //
/*

template <class It>
std::vector<typename It::value_type> merge(const It begin, const It mid,
                                           const It end) {
  std::vector<typename It::value_type> v;

  It it_l(begin), it_r(mid);
  const It it_mid(mid), it_end(end);

  while (it_l != it_mid && it_r != it_end) {
    v.push_back((*it_l <= *it_r) ? *it_l++ : *it_r++);
  }

  v.insert(v.end(), it_l, it_mid);
  v.insert(v.end(), it_r, it_end);

  return std::move(v);
}

*/

template <class It>
void internalNiceSort(It first, It last, const uint& n) {
  auto dist = std::distance(first, last);
  if (dist <= n) {
    // (last + 1) is in order to sort in range [first, last]
    std::sort(first, (last + 1));
    return;
  }

  std::array<std::thread, 2> arr;
  auto pivot = first + dist / 2;
  arr[0] = std::thread(internalNiceSort<It>, first, pivot, n);
  arr[1] = std::thread(internalNiceSort<It>, pivot + 1, last, n);

  for (auto& x : arr) {
    x.join();
  }

  // =============== Custom merge ====================
  // merge in ranges [first, pivot), [pivot + 1, last)
  // auto vec = merge(first, pivot + 1, last + 1);

  // =============== Standart merge ==================== //
  std::vector<typename It::value_type> vec(std::distance(first, last) + 1);
  std::merge(first, pivot + 1, pivot + 1, last + 1, vec.begin());
  std::move(vec.begin(), vec.end(), first);
}

template <class It>
void NiceSort(It first, It last) {
  auto n = std::distance(first, last) / std::thread::hardware_concurrency();
  internalNiceSort(first, last, n);
}

#endif

/*
// For testing
int main(int argc, char* argv[]) {
  std::vector<int> vec(VEC_SIZE);
  std::cout << "Initial vector: ";
  for (size_t i = 0; i < VEC_SIZE; ++i) {
    vec[i] = std::rand() % 100;
    std::cout << vec[i] << ' ';
  }

  std::cout << std::endl << std::endl;

  // Sorting
  NiceSort(vec.begin(), vec.end());

  std::cout << "Sorted vector: ";
  for (const int& x : vec) {
    std::cout << x << ' ';
  }

  std::cout << std::endl;

  return 0;
}
*/
