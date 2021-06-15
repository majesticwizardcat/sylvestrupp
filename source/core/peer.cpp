#include "core/peer.h"
#include "tools/tools.hpp"

#include <iostream>

Peer::~Peer() {
	if (m_connection.isActive()) {
		m_connection.terminate();
	}
}

void Peer::processMessages() {
	while (!m_messages.empty()) {
		const std::string& next = m_messages[0];
		std::cout << "Recieved: " << next << " from: " << m_connection.getName() << '\n';
		std::unique_ptr<Message> msg = parseFromJson(next);
		if (!msg) {
			std::cout << "Peer: " << m_connection.getName() << " sent bad message: "
				<< next << ". Closing connection" << '\n';
			m_connection.terminate();
			return;
		}
		switch(msg->messageType) {
		case MessageType::HELLO:
			processHelloMessage(dynamic_cast<HelloMessage*>(msg.get()));
			break;
		default:
			std::cout << "[NODE_ERROR]: Could not find message type" << '\n';
			m_connection.terminate();
		};
		m_messages.erase(m_messages.begin());
	}
}

void Peer::processHelloMessage(const HelloMessage* message) {
	if (m_handshake) {
		std::cout << "Double handshake from peer: " << m_connection.getName() << std::endl;
		m_connection.terminate();
		return;
	}
	m_handshake = true;
	if (m_starter) {
		return;
	}
	m_connection.send(HelloMessage().asJson());
}

void Peer::startWork(bool startCommunication) {
	m_starter = startCommunication;
	if (startCommunication) {
		m_connection.send(HelloMessage().asJson());
	}
	std::thread reader([&]() {
		while (m_connection.isActive()) {
			std::string msg = m_connection.read();
			if (msg.empty()) {
				continue;
			}
			std::vector<std::string> tokens = tools::tokeinize(msg, '\n');
			std::unique_lock<std::mutex> lck(m_queueLock);
			std::move(tokens.begin(), tokens.end(), std::back_inserter(m_messages));
			m_queueCondition.notify_all();
		}
	});
	while (m_connection.isActive()) {
		std::unique_lock<std::mutex> lck(m_queueLock);
		m_queueCondition.wait(lck);
		processMessages();
	}
	reader.join();
}