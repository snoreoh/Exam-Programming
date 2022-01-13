#pragma once

#include <optional>
#include <exception>

template <class T>
class MyOptional
{
	T* data;
	bool valid;
public:
	MyOptional() : data(nullptr), valid(false) {};
	MyOptional(std::nullopt_t) : data(nullptr), valid(false) {};
	MyOptional(const MyOptional<T>& other) : valid(other.valid) {
		if (valid) {
			data = new T;
			*data = *(other.data);
		}
		else data = nullptr;
	}
	MyOptional(MyOptional<T>&& other) : data(other.data), valid(other.valid) {
		other.data = nullptr;
		other.valid = false;
	}
	~MyOptional() {
		delete data;
	}
	MyOptional<T>& operator=(const MyOptional<T>& other){
		if (this != &other) {
			delete data;
			valid = other.valid;
			if (valid) {
				data = new T;
				*data = *(other.data);
			}
			else data = nullptr;
		}
		else return *this;
	}
	MyOptional<T>& operator=(MyOptional<T>&& other) {
		if (this != &other) {
			data = other.data;
			valid = other.valid;
			other.data = nullptr;
			other.valid = false;
		}
		else return *this;
	}
	T& operator*() {
		return *data;
	}
	T* operator->() {
		return data;
	}
	operator bool() const {
		return valid;
	}
	T& value() {
		return *data;
	}
	template <class U>
	T value_or(U&& default_value) {
		if (valid) return *data;
		else {
			try {
				return static_cast<T>(default_value);
			}
			catch (std::exception& e)
			{
				throw e;
			}
		}
	}
	friend MyOptional<T>& my_make_optional(const T& data) {
		MyOptional<T> res;
		res.data = new T;
		*(res.data) = data;
		res.valid = true;
		return res;
	}
};

