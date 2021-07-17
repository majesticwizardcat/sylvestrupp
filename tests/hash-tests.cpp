#include "crypto/hash.h"
#include "core/marabu-objects.h"

#include <iostream>

int main() {
	std::string json = GENESIS_BLOCK.asJson();
	std::cout << "Hashing genesis block: " << '\n';
	std::cout << json << '\n';
	std::string hash = hashing::SHA256AndEncode(json);
	std::cout << "Checking hash: ";
	if (hash == GENESIS_BLOCK_HASH) {
		std::cout << "PASS";
	}
	else {
		std::cout << "FAIL, got " << hash << " expected: " << GENESIS_BLOCK_HASH;
	}
	std::cout << '\n';
}
