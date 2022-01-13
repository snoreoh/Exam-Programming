#ifndef UNIQUE_LOCK_H_
#define UNIQUE_LOCK_H_

#include <atomic>
#include <mutex>
#include <system_error>

template <class Mutex>
class unique_lock {
 public:
  unique_lock() : mutex_(nullptr), owns_(false) {}
  explicit unique_lock(Mutex& m) : mutex_(&m), owns_(false) {
    lock();
    owns_ = true;
  }

  // Не лочим мютекс
  unique_lock(Mutex& m, std::defer_lock_t t) noexcept
      : mutex_(m), owns_(false) {}

  // Текущий поток уже должен был захватить его
  unique_lock(Mutex& m, std::adopt_lock_t t) : mutex_(&m), owns_(true){};

  unique_lock(unique_lock&& other) noexcept
      : mutex_(other.mutex_), owns_(other.owns_) {
    other.mutex_ = nullptr;
    other.owns_ = false;
  }

  unique_lock& operator=(unique_lock&& other) {
    if (owns_) {
      unlock();
    }

    mutex_ = other.mutex_;
    owns_ = other.owns_;
    other.mutex_ = nullptr;
    other.owns_ = false;
    return *this;
  }

  ~unique_lock() {
    if (owns_) {
      unlock();
    }
  }

  void lock() {
    if (!mutex_) {
      throw std::system_error(
          std::make_error_code(std::errc::operation_not_permitted));
    } else if (owns_) {
      throw std::system_error(
          std::make_error_code(std::errc::resource_deadlock_would_occur));
    } else {
      mutex_->lock();
      owns_ = true;
    }
  }

  void unlock() {
    if (!mutex_ || !owns_) {
      std::system_error(
          std::make_error_code(std::errc::operation_not_permitted));
    } else {
      mutex_->unlock();
      owns_ = false;
    }
  }

 private:
  Mutex* mutex_;
  std::atomic<bool> owns_;
};

#endif  // UNIQUE_LOCK_H_
