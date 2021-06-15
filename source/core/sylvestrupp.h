#pragma once

#include "networking/network.hpp"
#include "core/peer.h"
#include "core/constants.h"

const std::vector<std::pair<std::string, int>> BOOTSTRAP_IPS = {
	std::make_pair("keftes.di.uoa.gr", 18018),
	std::make_pair("covidnow.gr", 18018),
};

class Sylvestrupp {
private:
	TcpServer m_server;
	std::vector<Peer> m_peers;

	void bootstrap();

public:
	Sylvestrupp() : m_server(DEFAULT_PORT) { }

	void start();
	void connectTo(const std::string& ip, int port);
};
