#pragma once

#include <functional>
#include <algorithm>
#include <string>

// CryptoPP Includes
#include <config.h>
#include <sha.h>
#include <hex.h>

namespace hash {

inline std::string SHA256(const std::string& in) {
    CryptoPP::SHA256 hash;
    CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];
    CryptoPP::HexEncoder encoder;
    std::string output;
    hash.CalculateDigest(digest, (CryptoPP::byte*) in.c_str(), in.length());
    encoder.Attach(new CryptoPP::StringSink(output));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();
    std::for_each(output.begin(), output.end(), [](char & c){
        c = std::tolower(c);
    });
    return output;
}

inline int countZeros(char ch) {
    if (ch < '0') return 0;
    if (ch < '1') return 4;
    if (ch < '2') return 3;
    if (ch < '4') return 2;
    if (ch < '8') return 1;
    return 0;
}

int countZeros(const std::string& hash) {
    int sum = 0;
    for (const char* it = hash.c_str(); ; ++it) {
        int zeros = countZeros(*it);
        sum += zeros;
        if (zeros < 4)
            break;
    }
    return sum;
}

inline bool lessThanDifficulty(const std::string& hex, int difficulty) {
    return countZeros(hex) > difficulty;
}

}