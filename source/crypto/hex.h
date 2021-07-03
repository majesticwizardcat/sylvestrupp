#pragma once

#include <string>

class Hex;
class Hex64;

class Hex {
private:
	std::string m_number;

public:
	Hex() { }
	Hex(const Hex& other) : m_number(other.m_number) { }
	Hex(const std::string& number);
	Hex(int fixedSize);
	Hex(const Hex64& from64);

	Hex& operator++(int x);
	bool operator<(const Hex& other) const;
	bool operator==(const Hex& other) const;
	const std::string& value() const { return m_number; }
};

class Hex64 {
private:
	std::string m_number;

public:
	Hex64();
	Hex64(const std::string& number);
	Hex64(const Hex64& other);
	Hex64(const Hex& fromHex);

	Hex64& operator++(int x);
	bool operator<(const Hex64& other) const;
	bool operator==(const Hex64& other) const;
	const std::string& value() const { return m_number; }
};
