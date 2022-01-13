//
// Created by bayk on 02.01.2022.
//

#ifndef AL_EXAM_2021_SCOPED_PTR_H
#define AL_EXAM_2021_SCOPED_PTR_H

template <class T>
class scoped_ptr {
  T* _data;
 public:
  scoped_ptr(scoped_ptr<T>& other) = delete;
  scoped_ptr<T>& operator=(scoped_ptr<T>& other) = delete;
  scoped_ptr(scoped_ptr<T>&& other) = delete;
  scoped_ptr<T>& operator=(scoped_ptr<T>&& other) = delete;
  scoped_ptr(): _data(nullptr){}
  explicit scoped_ptr(T* pointer): _data(pointer){}
  ~scoped_ptr(){
    delete _data;
  }
  T* operator->(){
    return get();
  }
  T& operator*(){
    return *get();
  }
  T* get(){
    return _data;
  }
};

template<class T, class... Args >
scoped_ptr<T> make_scoped( Args&&... args ){
  return scoped_ptr<T>(new T(args...));
}

#endif  // AL_EXAM_2021_SCOPED_PTR_H
