#pragma once

class Sylvestrupp;

#include "core/network.h"
#include "core/peer.h"
#include "core/constants.h"

#include <string>
#include <mutex>
#include <map>

const std::vector<std::string> BOOTSTRAP_IPS = {
	"keftes.di.uoa.gr:18018",
	"covidnow.gr:18018",
};

class Sylvestrupp {
private:
	TcpServer m_server;
	std::map<std::string, Peer> m_peers;
	std::mutex m_peersLock;
	std::map<std::string, std::string> m_objectsCache;
	std::mutex m_objectsCacheLock;

	void bootstrap();

public:
	Sylvestrupp() : m_server(DEFAULT_PORT) { }

	void start();
	void connectTo(const std::string& ip, const std::string& port);

	// Node Managment (all methods should work async)
	Peer& addPeer(Peer peer, bool starter);
	std::vector<std::string> getPeerIpsCopy();
	void addNewPeers(const std::vector<std::string>& peers);
	bool addObject(const std::string& key, const std::string& value);
	bool objectExists(const std::string& key);
	bool getObject(const std::string& key, std::string* value);
	void peerFinished(const std::string& name);
	void broadcastMessage(const std::string& message);
};
