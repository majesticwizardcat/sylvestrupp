#include "crypto/hex.h"

#include <cmath>
#include <algorithm>

Hex::Hex(const std::string& number) : m_number(number) { }
Hex::Hex(int fixedSize) : m_number(fixedSize, '0') { }
Hex::Hex(const Hex64& from64) : m_number(from64.value()) { }

Hex& Hex::operator++(int x) {
	if (m_number.empty()) {
		m_number.push_back('1');
		return *this;
	}
	for (int i = m_number.size() - 1; i >= 0; --i) {
		m_number[i]++;
		if (m_number[i] == '9' + 1) {
			m_number[i] = 'a';
			break;
		}
		if (m_number[i] == 'f' + 1) {
			m_number[i] = '0';
			if (i == 0) {
				m_number.push_back('1');
				std::swap(m_number.back(), m_number[0]);
				break;
			}
		}
		else {
			break;
		}
	}
	return *this;
}

bool Hex::operator<(const Hex& other) const {
	int diff = std::abs((int) (m_number.size() - other.m_number.size()));
	std::string extra(diff, '0');
	std::string cpy(m_number);
	std::string otherCpy(other.m_number);
	if (cpy.size() < otherCpy.size()) {
		cpy.insert(0, extra);
	}
	else {
		otherCpy.insert(0, extra);
	}
	for (int i = 0; i < cpy.size(); ++i) {
		if (m_number[i] < other.m_number[i]) {
			return true;
		}
		else if (m_number[i] > other.m_number[i]) {
			return false;
		}
	}
	return false;
}

bool Hex::operator==(const Hex& other) const {
	int diff = std::abs((int) (m_number.size() - other.m_number.size()));
	std::string extra(diff, '0');
	std::string cpy(m_number);
	std::string otherCpy(other.m_number);
	if (cpy.size() < otherCpy.size()) {
		cpy.insert(0, extra);
	}
	else {
		otherCpy.insert(0, extra);
	}
	return cpy == otherCpy;
}

Hex64::Hex64() : m_number(64, '0') { }
Hex64::Hex64(const std::string& number) {
	int extra = 64 - number.size();
	if (extra < 0) {
		m_number = number.substr(0, 64);
		return;
	}
	m_number = std::string(extra, '0') + number;
}
Hex64::Hex64(const Hex64& other) : m_number(other.m_number) { }
Hex64::Hex64(const Hex& fromHex) : Hex64(fromHex.value()) { }

Hex64& Hex64::operator++(int x) {
	for (int i = 63; i >= 0; --i) {
		m_number[i]++;
		if (m_number[i] == '9' + 1) {
			m_number[i] = 'a';
			break;
		}
		if (m_number[i] == 'f' + 1) {
			m_number[i] = '0';
		}
		else {
			break;
		}
	}
	return *this;
}

bool Hex64::operator<(const Hex64& other) const {
	for (int i = 0; i < 64; ++i) {
		if (m_number[i] < other.m_number[i]) {
			return true;
		}
		if (m_number[i] > other.m_number[i]) {
			return false;
		}
	}
	return false;
}

bool Hex64::operator==(const Hex64& other) const {
	for (int i = 0; i < 64; ++i) {
		if (m_number[i] != other.m_number[i]) {
			return false;
		}
	}
	return true;
}
