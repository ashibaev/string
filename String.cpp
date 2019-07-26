#include "String.h"

#include <cstring>
#include <stdexcept>
#include <cctype>


String::String(const char* string) {
	Initialize(string, strlen(string));
}

String::String(const String& other) {
	Initialize(other.Data_, other.Size_);
}

String::String(String&& other) {
	Swap(other);
}

String::iterator String::begin() noexcept
{
	return Data_;
}

String::iterator String::end() noexcept
{
	return Data_ ? (Data_ + Size_) : nullptr;
}

String::const_iterator String::begin() const noexcept
{
	return Data_;
}

String::const_iterator String::end() const noexcept
{
	return Data_ ? (Data_ + Size_) : nullptr;
}

String::const_iterator String::cbegin() const noexcept
{
	return Data_;
}

String::const_iterator String::cend() const noexcept
{
	return Data_ ? (Data_ + Size_) : nullptr;
}

String& String::operator=(const String& other)
{
	if (this == &other)
		return *this;
	Initialize(other.Data_, other.Size_);
	return *this;
}

String& String::operator=(const char* other)
{
	Initialize(other, strlen(other));
	return *this;
}

String& String::operator=(String&& other)
{
	if (this == &other)
		return *this;
	delete[] Data_;
	Size_ = Capacity_ = 0;
	Swap(other);
	return *this;
}

bool String::Empty() const noexcept
{
	return Size_ == 0;
}

size_t String::Size() const noexcept
{
	return Size_;
}

size_t String::Length() const noexcept
{
	return Size_;
}

size_t String::Capacity() const noexcept
{
	return Capacity_;
}

const char* String::Data() const noexcept
{
	return Data_;
}

char* String::MutableData() noexcept
{
	return Data_;
}

String::~String() 
{
	delete[] Data_;
}

void String::Initialize(const char* string, size_t size)
{
	Reserve(GetNextCapacity(size));
	Size_ = size;
	memcpy(Data_, string, Size_ + 1);
}

size_t String::GetNextCapacity(size_t length)
{
	size_t currnetCapacity = Capacity_;
	if (currnetCapacity == 0)
		return 10;
	while (currnetCapacity <= length) {
		currnetCapacity <<= 1;
	}
	return currnetCapacity;
}

void String::Swap(String & other) noexcept {
	std::swap(Size_, other.Size_);
	std::swap(Capacity_, other.Capacity_);
	std::swap(Data_, other.Data_);
}

void String::Append(const char* string, size_t size)
{
	size_t new_size = Size_ + size;
	bool is_same_string = (string == Data_);
	Reserve(GetNextCapacity(new_size));
	if (is_same_string) {
		memcpy(Data_ + Size_, Data_, Size_);
	} else {
		strcpy(Data_ + Size_, string);
	}
	Size_ = new_size;
	Data_[Size_] = 0;
}

void String::Reserve(size_t new_capacity)
{
	if (new_capacity <= Capacity_) {
		return;
	}
	char* new_data = new char[new_capacity];
	memcpy(new_data, Data_, Size_);
	delete[] Data_;
	Data_ = new_data;
	Data_[Size_] = 0;
	Capacity_ = new_capacity;
}

void String::Clear() noexcept
{
	Size_ = 0;
	if (Capacity_ > 0) 
		Data_[0] = 0;
}


char& String::operator[](size_t index)
{
	return Data_[index];
}

char String::operator[](size_t index) const
{
	return Data_[index];
}

char& String::At(size_t index)
{
	if (index >= Size_)
		throw std::out_of_range("Index out of range");
	return Data_[index];
}

char String::At(size_t index) const
{
	if (index >= Size_)
		throw std::out_of_range("Index out of range");
	return Data_[index];
}

String& String::operator+=(const String& other)
{
	Append(other.Data_, other.Size_);
	return *this;
}

String& String::operator+=(const char* other)
{
	Append(other, strlen(other));
	return *this;
}

String& String::operator+=(char symbol)
{
	char str[2] = { symbol, 0 };
	Append(str, 1);
	return *this;
}

String operator+(const String& lhs, const String& rhs)
{
	return String(lhs) += rhs;
}

String operator+(String&& lhs, const String& rhs)
{
	return String(std::move(lhs)) += rhs;
}

std::istream& operator >> (std::istream& in, String& string) {
	string.Clear();
	char currentChar;
	while ((currentChar = in.get()) && isspace(currentChar)) {
		continue;
	}
	if (!currentChar) {
		return in;
	}
	string += currentChar;
	while ((currentChar = in.get()) && !isspace(currentChar)) {
		string += currentChar;
	}
	return in;
}

std::ostream& operator << (std::ostream& out, const String& string) {
	for (const auto& c : string) {
		out << c;
	}
	return out;
}

bool String::operator == (const String& other) const noexcept {
	if (this == &other)
		return true;
	if (Size_ != other.Size_) {
		return false;
	}
	return strcmp(Data_, other.Data_) == 0;
}

bool String::operator != (const String& other) const noexcept {
	return !(*this == other);
}