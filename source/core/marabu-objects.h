#pragma once

class MarabuObject;
enum class MarabuObjectType;

#include <string>

enum class MarabuObjectType {
	TRANSACTION, BLOCK
};

class MarabuObject {
public:
	std::string asHash() const;
	virtual std::string asJson() const = 0;
	virtual MarabuObjectType getType() const = 0;
};
