// Created by Dan10022002 on 08.01.2022

#include <stack>
#include <mutex>

template <class T>
class SafeStack {
    
    std::stack<T> _stack;
    std::mutex _mutex;
    
public:

    T Pop(){
        std::lock_guard<std::mutex> _lock(_mutex);
        T tmp = _stack.top();
        _stack.pop();
        return tmp;
    }
    
    void Push(const T& value){
        std::lock_guard<std::mutex> _lock(_mutex);
        _stack.push(value);
    }
    
    bool TryPop(T& value) {
    if(_mutex.try_lock()) {
        value = _stack.top();
        _stack.pop();
        mutex.unlock();
        return true;
    } else {
        return false;
    }
        
};
