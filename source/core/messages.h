#pragma once

#include "core/constants.h"

#include <memory>
#include <string>
#include <json.hpp>
#include <map>

const std::string MESSAGE_TYPE_HELLO = "hello";

const std::string TYPE = "type";
const std::string VERSION = "version";
const std::string AGENT = "agent";

enum class MessageType {
	HELLO,
};

const std::map<std::string, MessageType> GET_TYPE = {
	std::make_pair(MESSAGE_TYPE_HELLO, MessageType::HELLO),
};

class Message {
public:
	std::string type;
	MessageType messageType;

	Message() = delete;
	Message(const std::string& type) : type(type), messageType(GET_TYPE.at(type)) { }
	Message(const Message& other) : type(other.type) { }
	virtual ~Message() { }

	virtual std::string asJson() const = 0;
};

class HelloMessage : public Message {
public:
	std::string version;
	std::string agent;

	HelloMessage() : HelloMessage(LATEST_VERSION, NODE_NAME) { }
	HelloMessage(const std::string& version, const std::string& agent) :
		Message(MESSAGE_TYPE_HELLO), version(version), agent(agent) { }
	HelloMessage(const HelloMessage& other) : Message(other), version(other.version),
		agent(other.agent) { }
	~HelloMessage() { }

	std::string asJson() const {
		nlohmann::json msg
		{
			{TYPE, type},
			{VERSION, version},
			{AGENT, agent}
		};
		return msg.dump();
	}
};

std::unique_ptr<Message> parseHello(const nlohmann::json& json);
std::unique_ptr<Message> parseFromJson(const std::string& msg);
