#include "core/marabu-objects.h"
#include "crypto/hash.h"

std::string MarabuObject::asHash() const {
	return hashing::encodeHex(hashing::SHA256(asJson()));
}
