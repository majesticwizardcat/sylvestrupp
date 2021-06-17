#include "core/sylvestrupp.h"
#include "tools/tools.h"

#include <string>

void Sylvestrupp::bootstrap() {
	std::cout << "Bootstraping..." << '\n';
	for (const auto& c : BOOTSTRAP_IPS) {
		std::cout << "Connecting to: " << c << '\n';
		auto ipAndPort = tools::breakNameToParts(c);
		if (ipAndPort.has_value()) {
			connectTo(ipAndPort.value().first, ipAndPort.value().second);
		}
	}
}

Peer& Sylvestrupp::addPeer(Peer peer, bool starter) {
	std::cout << "Adding peer: " << peer.getName() << '\n';
	std::lock_guard<std::mutex> lck(m_peersLock);
	Peer* created = &(m_peers.insert(std::make_pair(peer.getName(), std::move(peer))).first->second);
	auto startWorker = [](Peer* peerPtr, bool shouldStart) {
		peerPtr->startWork(shouldStart);
	};
	std::thread(startWorker, created, starter).detach();
	return *created;
}

void Sylvestrupp::connectTo(const std::string& ip, const std::string& port) {
	TcpClient cl(ip, port);
	if (m_peers.find(cl.getName()) != m_peers.end()) {
		return;
	}
	addPeer(std::move(Peer(std::move(cl.start()), this)), true);
}

std::vector<std::string> Sylvestrupp::getPeerIpsCopy() {
	std::vector<std::string> ips;
	{
		std::lock_guard<std::mutex> lck(m_peersLock);
		for (const auto& peer : m_peers) {
			ips.push_back(peer.second.getName());
		}
	}
	return ips;
}

void Sylvestrupp::addNewPeers(const std::vector<std::string>& peers) {
	for (const auto& peer : peers) {
		auto ipAndPort = tools::breakNameToParts(peer);
		if (ipAndPort.has_value()
		&& m_peers.find(TcpClient(ipAndPort.value().first, ipAndPort.value().second).getName()) == m_peers.end()) {
			connectTo(ipAndPort.value().first, ipAndPort.value().second);
		}
	}
}

void Sylvestrupp::start() {
	bootstrap();
	while (true) {
		std::cout << "Listening for connections..." << '\n';
		Connection connection = m_server.accept();
		std::cout << "Got new connection: " << connection.getName() << '\n';
		addPeer(std::move(Peer(std::move(connection), this)), false);
	}
}
