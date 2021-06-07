#include <iostream>
#include <functional>
#include <algorithm>

#include <asio.hpp>
#include <config.h>
#include <sha.h>
#include <hex.h>

int main() {
    CryptoPP::SHA256 hash;
    CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];
    std::string message = "abcdefghijklmnopqrstuvwxyz";

    hash.CalculateDigest( digest, (CryptoPP::byte*) message.c_str(), message.length() );

    CryptoPP::HexEncoder encoder;
    std::string output;
    encoder.Attach( new CryptoPP::StringSink( output ) );
    encoder.Put( digest, sizeof(digest) );
    encoder.MessageEnd();

    std::for_each(output.begin(), output.end(), [](char & c){
        c = ::tolower(c);
    });
    std::cout << "SHA256 of: " << message << " is: " << output << std::endl;  
}