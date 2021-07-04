#include "core/network.h"

asio::io_service SYLV_IO_SERVICE;

Connection::Connection(asio::ip::tcp::socket socket,
	const std::string& name,
	const std::string& ip,
	const std::string& port)
	: m_socket(std::move(socket)),
	m_name(name),
	m_ip(ip),
	m_port(port),
	m_alive(true) { }

Connection::Connection(Connection&& other)
	: m_socket(std::move(other.m_socket)),
	m_alive(std::move(other.m_alive)),
	m_name(std::move(other.m_name)),
	m_ip(std::move(other.m_ip)),
	m_port(std::move(other.m_port)) { }

Connection& Connection::operator=(Connection other) {
	std::swap(m_socket, other.m_socket);
	std::swap(m_alive, other.m_alive);
	std::swap(m_ip, other.m_ip);
	std::swap(m_port, other.m_port);
	std::swap(m_name, other.m_name);
	return *this;
}

std::string Connection::read() {
	if (!m_alive) {
		return "";
	}
	try {
		asio::streambuf buf;
		asio::read_until(m_socket, buf, '\n');
		return asio::buffer_cast<const char*>(buf.data());
	}
	catch (const std::exception& e) {
		m_alive = false;
	}
	return "";
}

bool Connection::send(const std::string& message) {
	if (!m_alive) {
		return false;
	}
	try {
		asio::write(m_socket, asio::buffer(message + '\n'));
		return true;
	}
	catch (const std::exception& e) {
		m_alive = false;
		return false;
	}
}

void Connection::terminate() {
	if (!m_alive) {
		return;
	}
	m_alive = false;
	try {
		m_socket.close();
	}
	catch (const std::exception& e) { }
}

TcpClient::TcpClient(const std::string& ip, const std::string& port) {
	asio::ip::tcp::resolver::query resolver_query(ip,
		port, asio::ip::tcp::resolver::query::numeric_service);
	asio::ip::tcp::resolver resolver(SYLV_IO_SERVICE);
	asio::ip::tcp::resolver::iterator it =
		resolver.resolve(resolver_query);
	m_endpoint = it->endpoint();
	m_ip = m_endpoint.address().to_string();
	m_port = std::to_string(m_endpoint.port());
	m_name = m_ip + ':' + m_port;
}

Connection TcpClient::start() {
	asio::ip::tcp::socket socket(SYLV_IO_SERVICE);
	try {
		socket.connect(m_endpoint);
	}
	catch (const std::exception& e) { 
		Connection c(std::move(socket), m_name, m_ip, m_port);
		c.terminate();
		return std::move(c);
	}
	return Connection(std::move(socket), m_name, m_ip, m_port);
}

Connection TcpServer::accept() {
	asio::ip::tcp::acceptor acceptor(SYLV_IO_SERVICE, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), m_port));
	asio::ip::tcp::socket socket(SYLV_IO_SERVICE);
	try {
		acceptor.accept(socket);
	}
	catch (const std::exception& e) {
		Connection connection(std::move(socket), "", "", "");
		connection.terminate();
		return std::move(connection);
	}
	std::string ip = socket.remote_endpoint().address().to_string();
	std::string port = std::to_string(socket.remote_endpoint().port());
	std::string name = ip + ':' + port;
	return Connection(std::move(socket), name, ip, name);
}
