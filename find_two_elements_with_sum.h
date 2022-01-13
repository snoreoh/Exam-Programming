//
// Created by bayk on 03.01.2022.
//

#ifndef EXAM_FIND_TWO_ELEMENTS_WITH_SUM_H
#define EXAM_FIND_TWO_ELEMENTS_WITH_SUM_H

#include <utility>

//претендент на самое сложное задание :)
template <typename Iterator, typename T>
std::pair<bool, std::pair<Iterator, Iterator>> find_two_elements_with_sum( Iterator first, Iterator last, T c ){
  T sum;
  while (first != last){
    sum = *first + *last;
    if (sum == c){
      return {true, {first, last}};
    } else if (sum > c){
      --last;
    } else {
      ++first;
    }
  }
  return {false, {first, last}};
}

#endif  // EXAM_FIND_TWO_ELEMENTS_WITH_SUM_H
