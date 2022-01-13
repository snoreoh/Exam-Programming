#ifndef ANY_HPP_
#define ANY_HPP_

#include <any>
#include <optional>

// We must follow the rule of 5
class MyAny {
  struct Base {
    virtual ~Base(){};
    virtual Base* getCopy() = 0;
    virtual const std::type_info& type() const = 0;
  };

  template <class T>
  struct Derived : Base {
    T value;

    Derived(const T& value) : value(value){};
    Base* getCopy() { return new Derived<T>(value); }
    const std::type_info& type() const { return typeid(value); }
  };

  Base* storage;

 public:
  // constructors & destructors
  MyAny() : storage(nullptr){};

  template <class U>
  explicit MyAny(const U& value) : storage(new Derived<U>(value)){};
  MyAny(const MyAny& other) : storage(other.storage->getCopy()){};
  MyAny(MyAny&& other) : storage(other.storage) { other.storage = nullptr; }
  ~MyAny() { delete storage; }

  template <class U>
  MyAny(U&& other) : storage(new Derived<U>(std::forward<U>(other))) {}

  template <class U>
  MyAny& operator=(const std::optional<U>& value) {
    if (value) {
      delete storage;
      storage = new Derived<U>(value.value);
    }

    return *this;
  }

  const std::type_info& type() const noexcept { return storage->type(); }

  template <class ValueType>
  friend ValueType* my_any_cast(MyAny* operand);

  template <class ValueType>
  friend ValueType my_any_cast(const MyAny& operand);
};

template <class ValueType>
ValueType my_any_cast(const MyAny& val) {
  // Dereferencing problem while compiling. Let's copy-paste
  // using U_ = std::remove_cv_t<std::remove_reference_t<ValueType>>;
  // return static_cast<ValueType>(*my_any_cast<U_>(&operand));

  auto operand = &val;
  if (typeid(ValueType) == operand->type()) {
    return static_cast<MyAny::Derived<ValueType>*>(operand->storage)->value;
  }

  throw std::bad_any_cast();
}

template <class ValueType>
ValueType* my_any_cast(MyAny* operand) {
  if (!operand) {
    return nullptr;
  }

  if (typeid(ValueType) == operand->type()) {
    return &static_cast<MyAny::Derived<ValueType>*>(operand->storage)->value;
  } else {
    throw std::bad_any_cast();
  }
}

#endif
