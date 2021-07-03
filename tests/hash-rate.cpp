#include "crypto/hex.h"
#include "crypto/hash.h"

#include <json.hpp>
#include <iostream>
#include <chrono>

std::string TEST_TARGET = "00000002af000000000000000000000000000000000000000000000000000000";

int main() {
	Hex64 nonce;
	int hashes = 0;
	std::string hash;
	auto target = hashing::decodeHex(TEST_TARGET);
	int found = 0;
	nlohmann::json msg;
	std::vector<int> v;
	msg["T"] = "00000002af000000000000000000000000000000000000000000000000000000";
	msg["created"] = 1624219079;
	msg["miner"] = "dionyziz";
	msg["nonce"] = "0000000000000000000000000000000000000000000000000000002634878840";
	msg["note"] = "The Economist 2021-06-20: Crypto-miners are probably to blame for the graphics-chip shortage";
	msg["previd"] = nullptr;
	msg["txids"] = v;
	msg["type"] = "block";
	std::string dumped = msg.dump();
	std::cout << "Looking for: " << hashing::encodeHex(hashing::SHA256(dumped)) << '\n';
	std::string prefix = dumped.substr(0, dumped.find("\"nonce\":") + 9);
	std::string postfix = dumped.substr(dumped.find("\"nonce\":") + 64 + 9, dumped.size());
	for (auto& c : prefix) {
		if (c == '\'') {
			c = '"';
		}
	}
	for (auto& c : postfix) {
		if (c == '\'') {
			c = '"';
		}
	}
	nonce = Hex64();
	if ((prefix + "0000000000000000000000000000000000000000000000000000002634878840" + postfix)
		== dumped){ 
		std::cout << "Dumped == prefix + nonce + postfix" << '\n';
	}
	else {
		std::cout << "Dumped != prefix + nonce + postfix" << '\n';
	}
	auto start = std::chrono::high_resolution_clock::now();
	while ((std::chrono::high_resolution_clock::now() - start).count() < 1000000000) {
		auto hash = hashing::SHA256(prefix + nonce.value() + postfix);
		if (hashing::compareBytes(hash, target)) {
			found++;
		}
		nonce++;
		hashes++;
	}
	std::cout << "Hash rate: " << hashes << " / second" << " found: " << found << '\n';
	nonce = Hex64();
	auto cur = std::chrono::high_resolution_clock::now();
	while (true) {
		hash = hashing::SHA256(prefix + nonce.value() + postfix);
		if (hashing::compareBytes(hash, target)) {
			break;
		}
		nonce++;
	}
	auto after = std::chrono::high_resolution_clock::now();
	std::cout << "Time took to find a hash for target: " << TEST_TARGET
		<< " is: " << (after - cur).count() / 1000000000 << " seconds" << '\n';
	std::cout << "hash: " << hashing::encodeHex(hash) << '\n';
	std::cout << "block: \n" << prefix + nonce.value() + postfix << "\n";
}
