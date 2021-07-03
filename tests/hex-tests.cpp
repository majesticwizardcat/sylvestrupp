#include <iostream>

#include "crypto/hex.h"

void testIncrement(const char* input, const char* expected) {
	Hex in(input);
	Hex exp(expected);
	in++;
	std::cout << input << "++ == " << expected << ": ";
	if (in == exp) {
		std::cout << "PASS" << '\n';
	}
	else {
		std::cout << "FAIL, got " << in.value()
			 << " expected " << exp.value() << '\n';
	}
}

void testLessThan(const char* h0, const char* h1) {
	Hex first(h0);
	Hex second(h1);
	std::cout << h0 << " < " << h1 << ": ";
	if (first < second) {
		std::cout << "PASS" << '\n';
	}
	else {
		std::cout << "FAIL" << '\n';
	}
}

void testIncrement64(const char* input, const char* expected) {
	Hex64 in(input);
	Hex64 exp(expected);
	in++;
	std::cout << input << "++ == " << expected << ": ";
	if (in == exp) {
		std::cout << "PASS" << '\n';
	}
	else {
		std::cout << "FAIL, got " << in.value()
			 << " expected " << exp.value() << '\n';
	}
}

void testLessThan64(const char* h0, const char* h1) {
	Hex64 first(h0);
	Hex64 second(h1);
	std::cout << h0 << " < " << h1 << ": ";
	if (first < second) {
		std::cout << "PASS" << '\n';
	}
	else {
		std::cout << "FAIL" << '\n';
	}
}

int main() {
	testIncrement("", "1");
	testIncrement("0", "1");
	testIncrement("9", "a");
	testIncrement("f", "10");
	testIncrement("ff", "100");
	testIncrement("ffa", "ffb");
	std::cout << "--------------------" << '\n';
	testLessThan("0", "1");
	testLessThan("1", "2");
	testLessThan("0", "f");
	testLessThan("1", "10");
	testLessThan("00", "1");
	testLessThan("00002", "f");
	testLessThan("f0002", "f0a00");
	std::cout << "--------------------" << '\n';
	testIncrement64("0000000000000000000000000000000000000000000000000000000000000000",
					"0000000000000000000000000000000000000000000000000000000000000001");
	testIncrement64("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff",
					"0000000000000000000000000000000000000000000000000000000000000000");
	testIncrement64("f000000000000000000000000000000000000000000000000000000000000000",
					"f000000000000000000000000000000000000000000000000000000000000001");
	testIncrement64("fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffe",
					"ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
	testIncrement64("00000000000000000000000000000000000000000000000000000000000000ff",
					"0000000000000000000000000000000000000000000000000000000000000100");
	testIncrement64("0000000000000000000000000000000000000000000000000000000000000ffa",
					"0000000000000000000000000000000000000000000000000000000000000ffb");
	std::cout << "--------------------" << '\n';
	testLessThan64("0000000000000000000000000000000000000000000000000000000000000000",
				   "0000000000000000000000000000000000000000000000000000000000000001");
	testLessThan64("0000000000000000000000000000000000000000000000000000000000000000",
				   "f000000000000000000000000000000000000000000000000000000000000000");
	testLessThan64("f000000000000000000000000000000000000000000000000000000000000000",
				   "f000000000000000000000000000000000000000000000000000000000000001");
	testLessThan64("fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffe",
				   "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
}
