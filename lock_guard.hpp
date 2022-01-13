#ifndef LOCK_GUARD_H_
#define LOCK_GUARD_H_
#include <mutex>

// Аккуратно, очень сложное задание)))
template <class Mutex>
class lock_guard {
 public:
  explicit lock_guard(Mutex& m) : mutex_(m) { mutex_.lock(); }
  // Предполагает, что текущий поток уже захватил non-shared мьютекс
  lock_guard(Mutex& m, std::adopt_lock_t t) : mutex_(m) {}
  ~lock_guard() { mutex_.unlock(); }

  lock_guard(const lock_guard&) = delete;
  lock_guard& operator=(const lock_guard&) = delete;

 private:
  // Ссылочный тип данных удаляет конструктор по умолчанию!
  // В этом классе он нам и не нужен
  Mutex& mutex_;
};

#endif  // LOCK_GUARD_H_
