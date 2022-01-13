//
// Created by bayk on 03.01.2022.
//

#ifndef EXAM_SHARED_PTR_H
#define EXAM_SHARED_PTR_H

#include <atomic>

struct control_block{
  std::atomic<int> reference_counter = 1;
};

template <class T>
class shared_ptr {
  T* _data;
  control_block* _cb;
 public:
  shared_ptr(): _data(nullptr), _cb(nullptr){}
  ~shared_ptr(){
    if (_cb != nullptr && _cb->reference_counter > 1){
      --_cb->reference_counter;
    } else {
      delete _cb;
      delete _data;
    }
  }
  shared_ptr(shared_ptr<T>&& other): _data(other._data), _cb(other._cb){
    other._data = other._cb = nullptr;
  }
  shared_ptr<T>& operator=(shared_ptr<T>&& other){
    if (&other != this){
      _data = other._data;
      _cb = other._cb;
      other._data = other._cb = nullptr;
    }
  }
  shared_ptr(const shared_ptr<T>& other): _data(other._data), _cb(other._cb){
    if (_cb != nullptr){
      ++_cb->reference_counter;
    }
  }
  shared_ptr<T>& operator=(const shared_ptr<T>& other){
    if (&other != this){
      _data = other._data;
      _cb = other._cb;
      if (_cb != nullptr){
        ++_cb->reference_counter;
      }
    }
    return *this;
  }
  void reset(T* ptr = nullptr){
    if (_cb != nullptr){
      if (_cb->reference_counter > 1){
        --_cb->reference_counter;
      } else {
        delete _data;
        delete _cb;
      }
    }
    if (ptr != nullptr){
      _cb = new control_block;
    } else {
      _cb = nullptr;
    }
    _data = ptr;
  }
  T* release() {
    if (_cb != nullptr) {
      if (_cb->reference_counter > 1) {
        --_cb->reference_counter;
      } else {
        delete _cb;
      }
    }
    T* temp = _data;
    delete _data;
    return temp;
  }
  void swap(shared_ptr<T> &other) {
    T* temp_data = _data;
    control_block* temp_cb = _cb;
    _data = other._data;
    _cb = other._cb;
    other._data = temp_data;
    other._cb = temp_cb;
  }
  T* operator->(){
      return get();
  }
  T& operator*(){
    return *get();
  }
  operator bool() const{
      return _data != nullptr;
  }
  T* get(){
    return _data;
  }
};

#endif  // EXAM_SHARED_PTR_H
