//
// Created by bayk on 03.01.2022.
//

#ifndef EXAM_SAFE_QUEUE_H
#define EXAM_SAFE_QUEUE_H

#include <queue>
#include <mutex>

template <class T>
class SafeQueue {
  std::queue<T> _data;
  std::mutex mutex;
 public:
  T Pop(){
    mutex.lock();
    T temp = _data.front();
    _data.pop();
    mutex.unlock();
    return temp;
  }
  void Push(const T& value){
    mutex.lock();
    _data.push(value);
    mutex.unlock();
  }
  bool TryPop(T& value){
    if(mutex.try_lock()){
      value = _data.front();
      _data.pop();
      mutex.unlock();
      return true;
    } else {
      return false;
    }
  }
};

#endif  // EXAM_SAFE_QUEUE_H
