#pragma once
#include <iostream>
#include <type_traits>
#include <iomanip>
#include <variant>
#include <string>
#include <vector>
#include <map>

namespace dim {
	class Range {
	private:
		class Iterator {
		public:
			Iterator(int start, int end, int step) : start_(start), end_(end), step_(step) {}
			bool operator!=(const Iterator& other) { return this->start_ != other.start_; }
			int operator*() const { return this->start_; }
			Iterator& operator++() {
				start_ += step_;
				if ((this->step_ > 0 && this->start_ >= this->end_) || (this->step_ < 0 && this->start_ <= this->end_)) { this->start_ = this->end_; }
				return *this;
			}
		private:
			int start_ = 0, end_, step_ = 1;
		};
		
	public:
		Range(int end): end_(end) {}
		Range(int start, int end) : start_(start), end_(end) {}
		Range(int start, int end, int step) : start_(start), end_(end), step_(step) { if (step < 1) { throw std::runtime_error("��� �� ������ ���� ������ 1"); } }

		Iterator begin() const { return Iterator(this->start_, this->end_, this->step_); }
		Iterator end() const { return Iterator(this->end_, this->start_, this->step_); }
	private:
		int start_ = 0, end_, step_ = 1;
	};
	template<typename T>
	void println(const T& value) {
		std::cout << std::boolalpha << value;
	}

	template<typename T, typename... Args>
	void println(const T& value, const Args&... args) {
		std::cout << std::boolalpha << value;
		dim::println(args...);
	}
}

using ValueTypes = std::variant<int, double, std::string, bool>; // ��������� ����
enum Type { TNull, TInt, TFloat, TString, TBool }; // ���� ������

// ��������� ���������
struct Variable {
	Type type_ = Type::TNull;
	ValueTypes value_;
	Variable() {}
	Variable(Type type, ValueTypes value): type_(type), value_(value) {}
};

// ����� ������������ ���������
class Dynamic {
public:
	Dynamic(): var(Type::TNull, nullptr) {}
	Dynamic(int value) : var(Type::TInt, int(value)) {}
	Dynamic(double value) : var(Type::TFloat, double(value)) {}
	Dynamic(const char* value) : var(Type::TString, std::string(value)) {}
	Dynamic(std::string value) : var(Type::TString, std::string(value)) {}
	Dynamic(bool value) : var(Type::TBool, value) {}

	friend Dynamic operator+(const Dynamic& lhs, const Dynamic& rhs);  // ���������� ���������� ��������
	friend Dynamic operator-(const Dynamic& lhs, const Dynamic& rhs);  // ���������� ���������� ���������
	friend Dynamic operator*(const Dynamic& lhs, const Dynamic& rhs);  // ���������� ���������� ���������
	friend Dynamic operator/(const Dynamic& lhs, const Dynamic& rhs);  // ���������� ���������� �������
	friend Dynamic operator%(const Dynamic& lhs, const Dynamic& rhs);  // ���������� ���������� �������

	friend bool operator<(const Dynamic& lhs, const Dynamic& rhs);	// ���������� ���������� ������
	friend bool operator==(const Dynamic& lhs, const Dynamic& rhs);  // ���������� ���������� ����������
	friend bool operator>(const Dynamic& lhs, const Dynamic& rhs);  // ���������� ���������� ������
	friend bool operator!=(const Dynamic& lhs, const Dynamic& rhs);  // ���������� ���������� �� �����
	friend bool operator<=(const Dynamic& lhs, const Dynamic& rhs);  // ���������� ���������� ������ ���� �����
	friend bool operator>=(const Dynamic& lhs, const Dynamic& rhs);  // ���������� ���������� ������ ���� �����
	friend std::ostream& operator<<(std::ostream& os, const Dynamic& dynamic); // �������� ������

	std::string GetType() { return type.at(this->var.type_); }
private:
	Variable var;
	std::map<Type, std::string> type = {
		{Type::TNull, "null"}, {Type::TInt, "int"}, {Type::TFloat , "double"},
		{Type::TString, "string"}, {Type::TBool, "bool"}
	};
};

// ������� ��� �������� �������� �������� � �����
template<typename T, typename U>
Dynamic Add(const T& lhs, const U& rhs) {
	if constexpr (std::is_arithmetic_v<T> && std::is_arithmetic_v<U>) { return lhs + rhs; }
	if constexpr (std::is_same_v<T, U>) { return lhs + rhs; }
	return Dynamic();
}

// ������� ��� ��������� �������� ��������
template<typename T, typename U>
Dynamic Sub(const T& lhs, const U& rhs) {
	if constexpr (std::is_arithmetic_v<T> && std::is_arithmetic_v<U>) { return lhs - rhs; }
	return Dynamic();
}

// ������� ��� ��������� �������� �������� � �����
template<typename T, typename U>
Dynamic Mul(const T& lhs, const U& rhs) {
	if constexpr (std::is_arithmetic_v<T> && std::is_convertible_v<U, std::string>) {
		std::string result;
		for (size_t i = 0; i < lhs; ++i) { result += rhs; }
		return result;
	}
	else if constexpr (std::is_arithmetic_v<T> && std::is_arithmetic_v<U>) { return lhs * rhs; }
	return Dynamic();
}

// ������� ��� ������� �������� ��������
template<typename T, typename U>
Dynamic Div(const T& lhs, const U& rhs) {
	if constexpr (std::is_arithmetic_v<T> && std::is_arithmetic_v<U>) { return lhs / rhs; }
	return Dynamic();
}

// ������� ��� ���������� ������� �� ������� ������������� ��������
template<typename T, typename U>
Dynamic Mod(T& lhs, U& rhs) {
	if constexpr (std::is_arithmetic_v<T> && std::is_arithmetic_v<U>) {  }
	return Dynamic();
}

// ������� ��� ���������� �������� ��������
template<typename T, typename U>
bool Less(const T& lhs, const U& rhs) {
	if constexpr (std::is_arithmetic_v<T> && std::is_arithmetic_v<U>) { return lhs < rhs; }
	return false;
}

// ������� ��� ���������� �������� ��������
template<typename T, typename U>
bool Greater(const T& lhs, const U& rhs) {
	if constexpr (std::is_arithmetic_v<T> && std::is_arithmetic_v<U>) { return lhs > rhs; }
	return false;
}

// ������� ��� ���������� ������� ��� �������� ��������
template<typename T, typename U>
bool LessEqual(const T& lhs, const U& rhs) {
	if constexpr (std::is_arithmetic_v<T> && std::is_arithmetic_v<U>) { return lhs <= rhs; }
	return false;
}

// ������� ��� ���������� �������� ��� ������� ��������
template<typename T, typename U>
bool GreaterEqual(const T& lhs, const U& rhs) {
	if constexpr (std::is_arithmetic_v<T> && std::is_arithmetic_v<U>) { return lhs >= rhs; }
	return false;
}

// ������� ��� ���������� ������� �������� 
template<typename T, typename U>
bool Equal(const T& lhs, const U& rhs) {
	if constexpr (std::is_arithmetic_v<T> && std::is_arithmetic_v<U>) { return lhs == rhs; }
	return false;
}

// ������� ��� ���������� �� ������� �������� 
template<typename T, typename U>
bool NotEqual(const T& lhs, const U& rhs) {
	if constexpr (std::is_arithmetic_v<T> && std::is_arithmetic_v<U>) { return lhs != rhs; }
	return false;
}

Dynamic operator+(const Dynamic& lhs, const Dynamic& rhs) { 
	return std::visit([](const auto& a, const auto& b){
		return Add(a, b);
	}, lhs.var.value_, rhs.var.value_);
}
Dynamic operator-(const Dynamic& lhs, const Dynamic& rhs) {
	return std::visit([](const auto& a, const auto& b) {
		return Sub(a, b);
	}, lhs.var.value_, rhs.var.value_);
}
Dynamic operator*(const Dynamic& lhs, const Dynamic& rhs) {
	return std::visit([](const auto& a, const auto& b) {
		return Mul(b, a);
	}, lhs.var.value_, rhs.var.value_);
}
Dynamic operator/(const Dynamic& lhs, const Dynamic& rhs) {
	return std::visit([](const auto& a, const auto& b) {
		return Div(a, b);
	}, lhs.var.value_, rhs.var.value_);
}
Dynamic operator%(const Dynamic& lhs, const Dynamic& rhs) {
	if (std::holds_alternative<int>(lhs.var.value_) && std::holds_alternative<int>(rhs.var.value_)) { return std::get<int>(lhs.var.value_) % std::get<int>(rhs.var.value_); }
	return Dynamic();
}

bool operator<(const Dynamic& lhs, const Dynamic& rhs) {
	return std::visit([](const auto& a, const auto& b) {
		return Less(a, b);
	}, lhs.var.value_, rhs.var.value_);
}
bool operator>(const Dynamic& lhs, const Dynamic& rhs) {
	return std::visit([](const auto& a, const auto& b) {
		return Greater(a, b);
		}, lhs.var.value_, rhs.var.value_);
}
bool operator==(const Dynamic& lhs, const Dynamic& rhs) {
	return std::visit([](const auto& a, const auto& b) {
		return Equal(a, b);
	}, lhs.var.value_, rhs.var.value_);
}
bool operator!=(const Dynamic& lhs, const Dynamic& rhs) {
	return std::visit([](const auto& a, const auto& b) {
		return NotEqual(a, b);
		}, lhs.var.value_, rhs.var.value_);
}
bool operator<=(const Dynamic& lhs, const Dynamic& rhs) {
	return std::visit([](const auto& a, const auto& b) {
		return LessEqual(a, b);
	}, lhs.var.value_, rhs.var.value_);
}
bool operator>=(const Dynamic& lhs, const Dynamic& rhs) {
	return std::visit([](const auto& a, const auto& b) {
		return GreaterEqual(a, b);
	}, lhs.var.value_, rhs.var.value_);
}

std::ostream& operator<<(std::ostream& os, const Dynamic& dynamic) {
	std::visit([&os](const auto& element) {
		os << element;
	}, dynamic.var.value_);
	return os;
}