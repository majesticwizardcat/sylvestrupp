#pragma once

class Peer;

#include "core/network.h"
#include "core/messages.h"
#include "core/sylvestrupp.h"

#include <string>
#include <vector>

class Peer {
private:
	Sylvestrupp* m_node;
	Connection m_connection;
	bool m_handshake;
	bool m_starter;
	bool m_running;
	std::vector<std::string> m_messages;

	std::string readNext();
	void processMessages();
	void processHelloMessage(const HelloMessage* message);
	void processGetPeersMessage(const GetPeersMessage* message);
	void processPeersMessage(const PeersMessage* message);
	void processIHaveObjectMessage(const IHaveObjectMessage* message);
	void processObjectMessage(const ObjectMessage* message);
	void processGetObjectMessage(const GetObjectMessage* message);

public:
	Peer() = delete;
	Peer(const Peer& other) = delete;
	Peer(Connection connection, Sylvestrupp* node) :
		m_connection(std::move(connection)),
		m_node(node),
		m_handshake(false),
		m_starter(false),
		m_running(false) { }
	Peer(Peer&& other) :
		m_connection(std::move(other.m_connection)),
		m_node(std::move(other.m_node)),
		m_handshake(std::move(other.m_handshake)),
		m_running(std::move(other.m_running)),
		m_starter(std::move(other.m_starter)),
		m_messages(std::move(other.m_messages)) { }
	~Peer();

	Peer& operator=(Peer other);

	void startWork(bool startCommunication);
	void sendMessage(const std::string& msg);
	inline bool isRunning() const { return m_running; }
	inline const std::string& getIp() const { return m_connection.getIp(); }
	inline const std::string& getPort() const { return m_connection.getPort(); }
	inline const std::string& getName() const { return m_connection.getName(); }
};