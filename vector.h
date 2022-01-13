//
// Created by bayk on 03.01.2022.
//

#ifndef EXAM_VECTOR_H
#define EXAM_VECTOR_H

#include <cstdlib>
#include <stdexcept>

template <class T>
class vector{
  T* _data;
  size_t _size;
  size_t _capacity;
  void check_capacity(){
    if (_size == _capacity){
      T* temp_data = _data;
      if (_capacity == 0){
        _capacity = 1;
      } else {
        _capacity *= 2;
      }
      _data = new T[_capacity];
      if (temp_data != nullptr){
        for (size_t i = 0; i < _size; ++i) {
          _data[i] = temp_data[i];
        }
      }
      delete temp_data;
    }
  }
 public:
  vector(): _data(nullptr), _size(0), _capacity(0){}
  vector(vector<T>&& other) noexcept : _data(other._data), _size(other._size), _capacity(other._capacity){
    other._data = nullptr;
  }
  vector(vector<T>& other): _size(other._size), _capacity(other._capacity){
    if (_capacity == 0){
      _data = nullptr;
    } else {
      _data = new T[_capacity];
      for (size_t i = 0; i < _size; ++i) {
        _data[i] = other._data[i];
      }
    }
  }
  vector<T>& operator=(vector<T>&& other) noexcept {
    if (this != &other){
      _data = other._data;
      _size = other._size;
      _capacity = other._capacity;
      other._data = nullptr;
    }
    return *this;
  }
  vector<T>& operator=(const vector<T>& other){
    if (this != &other) {
      _size = other._size;
      _capacity = other._capacity;
      if (_capacity == 0) {
        _data = nullptr;
      } else {
        _data = new int[_capacity];
        for (size_t i = 0; i < _size; ++i) {
          _data[i] = other._data[i];
        }
      }
    }
    return *this;
  }
  ~vector(){
    delete _data;
  }
  void push_back(const T& value){
    insert(_size, value);
//    либо можно посложнее
//    check_capacity();
//    _data[_size] = value;
//    ++_size;
  }
  T& operator[](int n){
    return _data[n];
  }

  void insert(int pos, T value){
    if (pos > _size){
      throw std::out_of_range("out of range");
    }
    check_capacity();
    for (int i = _size; i > pos; --i) {
      _data[i] = _data[i - 1];
    }
    _data[pos] = value;
    ++_size;
  }
  size_t size(){ // опционально
    return _size;
  }
};

#endif  // EXAM_VECTOR_H
