#include "core/sylvestrupp.h"

void Sylvestrupp::bootstrap() {
	std::cout << "Bootstraping..." << '\n';
	for (const auto& c : BOOTSTRAP_IPS) {
		std::cout << "Connecting to: " << c.first << ":" << c.second << '\n';
		connectTo(c.first, c.second);
	}
}

void Sylvestrupp::connectTo(const std::string& ip, int port) {
		TcpClient cl(ip, port);
		m_peers.emplace_back(std::move(cl.start()));
		m_peers.back().startWork(true);
}

void Sylvestrupp::start() {
	bootstrap();
	while (true) {
		m_peers.emplace_back(m_server.accept());
		m_peers.back().startWork(false);
	}
}
