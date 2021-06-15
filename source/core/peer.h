#pragma once

class Peer;

#include "networking/network.hpp"
#include "core/messages.h"

#include <string>
#include <vector>
#include <condition_variable>
#include <mutex>

class Peer {
private:
	Connection m_connection;
	bool m_handshake;
	bool m_starter;
	bool m_finished;
	std::vector<std::string> m_messages;
	std::mutex m_queueLock;
	std::condition_variable m_queueCondition;

	std::string readNext();
	void processMessages();
	void processHelloMessage(const HelloMessage* message);

public:
	Peer() = delete;
	Peer(const Peer& other) = delete;
	Peer(Connection connection) :
		m_connection(std::move(connection)),
		m_handshake(false),
		m_starter(false),
		m_finished(true) { }
	Peer(Peer&& other) :
		m_connection(std::move(other.m_connection)),
		m_handshake(std::move(other.m_handshake)),
		m_finished(std::move(other.m_finished)),
		m_starter(std::move(other.m_starter)),
		m_messages(std::move(other.m_messages)) { }
	~Peer();

	void startWork(bool startCommunication);
	inline bool isFinished() { return m_finished; }
};