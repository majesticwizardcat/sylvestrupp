#include "core/messages.h"

std::unique_ptr<Message> parseHello(const nlohmann::json& json) {
	if (json.find(STR_VERSION) == json.end()
		|| json.find(STR_AGENT) == json.end()) {
		return nullptr;
	}
	return std::make_unique<HelloMessage>(json.at(STR_VERSION), json.at(STR_AGENT));
}

std::unique_ptr<Message> parseFromJson(const std::string& msg) {
	nlohmann::json jsonMsg = nlohmann::json::parse(msg);
	if (jsonMsg.find(STR_TYPE) == jsonMsg.end()) {
		return nullptr;
	}
	const std::string& msgType = jsonMsg[STR_TYPE];
	if (msgType == MESSAGE_TYPE_HELLO) {
		return parseHello(jsonMsg);
	}
	return nullptr;
}