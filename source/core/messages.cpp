#include "core/messages.h"

std::unique_ptr<Message> parseHello(const nlohmann::json& json) {
	if (json.find(VERSION) == json.end()
		|| json.find(AGENT) == json.end()) {
		return nullptr;
	}
	return std::make_unique<HelloMessage>(json.at(VERSION), json.at(AGENT));
}

std::unique_ptr<Message> parseFromJson(const std::string& msg) {
	nlohmann::json jsonMsg = nlohmann::json::parse(msg);
	if (jsonMsg.find(TYPE) == jsonMsg.end()) {
		return nullptr;
	}
	const std::string& msgType = jsonMsg[TYPE];
	if (msgType == MESSAGE_TYPE_HELLO) {
		return parseHello(jsonMsg);
	}
	return nullptr;
}