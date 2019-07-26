#pragma once

#include <cstddef>
#include <iostream>

struct String {
public:
	using const_iterator = const char*;
	using iterator = char*;

    String(const char* string = "");

	String(const String& other);
	String(String&& other);

	String::iterator begin() noexcept;
	String::iterator end() noexcept;
	String::const_iterator begin() const noexcept;
	String::const_iterator end() const noexcept;
	String::const_iterator cbegin() const noexcept;
	String::const_iterator cend() const noexcept;

	String& operator = (const String& other);
	String& operator = (const char* other);
	String& operator = (String&& other);

	char& operator [] (size_t index);
	char operator [] (size_t index) const;

	char& At(size_t index);
	char At(size_t index) const;

	String& operator += (const String& other);
	String& operator += (const char* other);
	String& operator += (char symbol);

	bool operator == (const String& other) const noexcept;
	bool operator != (const String& other) const noexcept;

	void Reserve(size_t new_capacity);

	void Clear() noexcept;

	bool Empty() const noexcept;

	size_t Size() const noexcept;
	size_t Length() const noexcept;
	size_t Capacity() const noexcept;

	const char* Data() const noexcept;
	char* MutableData() noexcept;

	~String();

private:

	void Initialize(const char* string, size_t size);
	size_t GetNextCapacity(size_t length);
	void Swap(String& other) noexcept;
	void Append(const char* string, size_t size);

    size_t Size_ = 0;
	size_t Capacity_ = 0;
    char* Data_ = nullptr;
};


std::istream& operator >> (std::istream& in, String& string);
std::ostream& operator << (std::ostream& out, const String& string);

String operator + (const String& lhs, const String& rhs);
String operator + (String&& lhs, const String& rhs); 
