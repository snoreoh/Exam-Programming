// Copyright 2021 Andrey Nikolaev <andrey.n190402@gmail.com>

#ifndef INCLUDE_SHAREDPTR_HPP_
#define INCLUDE_SHAREDPTR_HPP_
#include <atomic>
#include <utility>

template <typename T>
class SharedPtr {
  T* p;
  std::atomic_uint* n;

 public:
  SharedPtr() : p(nullptr)
  {
      n = new std::atomic_uint(0);
  }

  ~SharedPtr() {
      if (n != nullptr && --(*n) == 0) {
          delete ptr_;
          delete n;
      }
      p = nullptr;
      n = nullptr;
  }

  SharedPtr(SharedPtr&& r) noexcept {
      p = std::move(r.p);
      n = std::move(r.n);
      r.p = nullptr;
      r.n = nullptr;
  }

  

  SharedPtr(const SharedPtr& r) : p(r.p), n(r.n) {
      ++(*n);
  }
  
  

  SharedPtr& operator=(const SharedPtr& r)  {
    if (this != &r) {
      if (n != nullptr) {
        if (--(*n) == 0) {
          delete p;
          delete n;
        }
      }
      p = r.p;
      n = r.n;
      if (p != nullptr) {
        ++(*n);
      }
    }
    return *this;
  }
  SharedPtr& operator=(SharedPtr&& r)  {
    if (this != &r) {
      if (n != nullptr) {
        if (--(*n) == 0) {
          delete p;
          delete n;
        }
      }
      p = std::move(r.p);
      n = std::move(r.n);
      r.p_ = nullptr;
      r.n = nullptr;
    }
    return *this;
  }

  operator bool() const { return p != nullptr; }
  auto operator*() const -> T& { return *p; }
  auto operator->() const -> T* { return p; }  //

  auto get() -> T* { return p; }

  
  void reset(T* ptr=nullptr) {
    if (n != nullptr && --(*n) == 0) {
      delete p;
      delete n;
    }
    p = ptr;
    n = new std::atomic_uint[1];
  }
  void swap(SharedPtr& r) {
    std::swap(p, r.p);
    std::swap(n, r.n);
  }
  
};

#endif  // INCLUDE_SHAREDPTR_HPP_
