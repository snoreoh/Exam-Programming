//
// Created by bayk on 01.01.2022.
//

#ifndef EXAM_UNIQUE_PTR_H
#define EXAM_UNIQUE_PTR_H

#include <cstdlib>

template <class T>
class unique_ptr {
    T* _data;
public:
    unique_ptr(): _data(nullptr){}
    ~unique_ptr(){
        delete _data;
    }
    explicit unique_ptr(T* ptr): _data(ptr){}
    unique_ptr(unique_ptr<T>&& other) noexcept: _data(other._data) {
        other._data = nullptr;
    }
    unique_ptr<T>& operator=(unique_ptr<T>&& other) noexcept{
        _data = other._data;
        other._data = nullptr;
        return *this;
    }
    void reset(T* ptr = nullptr){
        delete _data;
        _data = ptr;
    }
    T* release(){
        T* temp = _data;
        _data = nullptr;
        return temp;
    }
    void swap(unique_ptr& other){
        T* temp = _data;
        _data = other._data;
        other._data = temp;
    }
    T* operator->(){
        return get();
    }
    T& operator*(){
        return *get();
    }
    explicit operator bool() const{
        return _data != nullptr;
    }
    T* get(){
        return _data;
    }
};

template<class T, class... Args >
unique_ptr<T> make_unique( Args&&... args ){
    return unique_ptr<T>(new T(args...));
}

#endif //EXAM_UNIQUE_PTR_H

