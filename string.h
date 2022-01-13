//
// Created by bayk on 03.01.2022.
//

#ifndef EXAM_STRING_H
#define EXAM_STRING_H

#include <cstdlib>

class string{
 public:
  char* _data;
  string(): _data(nullptr){}
  size_t size() const{
    size_t i = 0;
    if (_data != nullptr){
      while (_data[i] != '\0'){
        ++i;
      }
    }
    return i;
  }
  string(string&& other) noexcept : _data(other._data){
    other._data = nullptr;
  }
  string(string& other){
    if (other._data == nullptr){
      _data = nullptr;
    } else {
      size_t _size = other.size();
      _data = new char [_size];
      for (size_t i = 0; i < _size; ++i) {
        _data[i] = other._data[i];
      }
    }
  }
  string& operator=(string&& other) noexcept {
    if (this != &other){
      _data = other._data;
      other._data = nullptr;
    }
    return *this;
  }
  string& operator=(const string& other){
    if (this != &other){
      if (other._data == nullptr){
        _data = nullptr;
      } else {
        size_t _size = other.size();
        _data = new char [_size];
        for (size_t i = 0; i < _size; ++i) {
          _data[i] = other._data[i];
        }
      }
    }
    return *this;
  }
  explicit string(const char* other){
    size_t _size = 0;
    while (other[_size] != '\0') {
      _size++;
    }
    _data = new char [_size + 1];
    for (size_t i = 0; i < _size; ++i) {
      _data[i] = other[i];
    }
    _data[_size] = '\0';
  }
  ~string(){
    delete[] _data;
  }
  char& operator[](int n) const{
    return _data[n];
  }
  string& append(const string& str){
    size_t _size = size(), str_size = str.size();
    char* temp = new char [_size + str_size];
    for (size_t i = 0; i < _size; ++i) {
      temp[i] = _data[i];
    }
    for (size_t i = 0; i < str_size; ++i) {
      temp[_size + i] = str._data[i];
    }
    temp[_size + str_size] = '\0';
    delete[] _data;
    _data = temp;
    return *this;
  }
  string& replace(size_t pos,  size_t len,  const string& str){
    size_t _size = size(), str_size = str.size();
    if (pos > _size){
      throw std::out_of_range("out of range");
    }
    char* temp = new char [_size - len + str_size];
    for (size_t i = 0; i < pos; ++i) {
      temp[i] = _data[i];
    }
    for (size_t i = 0; i < str_size; ++i) {
      temp[pos + i] = str._data[i];
    }
    for (size_t i = pos + len; i < _size; ++i) {
      temp[str_size - len + i] = _data[i];
    }
    temp[_size - len + str_size] = '\0';
    delete[] _data;
    _data = temp;
    return *this;
  }
//  хз как реализовывать, потому что надо создавать полностью класс итераторов
//  template <typename iterator>
//  string& replace (iterator first, iterator last, const string& str);
};

#endif  // EXAM_STRING_H
