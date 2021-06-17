#pragma once 

#include <asio.hpp>
#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <utility>

class Connection {
private:
    asio::ip::tcp::socket m_socket;
	bool m_alive;
	std::string m_ip;
	std::string m_port;
	std::string m_name;

public:
    Connection() = delete;
    Connection(const Connection& other) = delete;
    Connection(asio::ip::tcp::socket socket, const std::string& name, const std::string& ip,
		const std::string& port)
		: m_socket(std::move(socket)),
		m_name(name),
		m_ip(ip),
		m_port(port),
		m_alive(true) { }
    Connection(Connection&& other)
		: m_socket(std::move(other.m_socket)),
		m_alive(std::move(other.m_alive)),
		m_name(std::move(other.m_name)),
		m_ip(std::move(other.m_ip)),
		m_port(std::move(other.m_port)) { }

	Connection& operator=(Connection other) {
		std::swap(m_socket, other.m_socket);
		std::swap(m_alive, other.m_alive);
		std::swap(m_ip, other.m_ip);
		std::swap(m_port, other.m_port);
		std::swap(m_name, other.m_name);
		return *this;
	}

    std::string read() {
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

    bool send(const std::string& message) {
		if (!m_alive) {
			return false;
		}
		try {
			const std::string msg = message + '\n';
			asio::write(m_socket, asio::buffer(msg));
			return true;
		}
		catch (const std::exception& e) {
			m_alive = false;
			return false;
		}
    }

	void terminate() {
		if (!m_alive) {
			return;
		}
		m_alive = false;
		try {
			m_socket.close();
		}
		catch (const std::exception& e) { }
	}
    
    inline bool isActive() const { return m_alive; }
	inline const std::string& getIp() const { return m_ip; }
	inline const std::string& getPort() const { return m_port; }
	inline const std::string& getName() const { return m_name; }
};

class TcpClient {
private:
	asio::ip::tcp::endpoint m_endpoint;
	std::string m_ip;
	std::string m_name;
	std::string m_port;
    
public:
    TcpClient() = delete;
    TcpClient(const TcpClient& other) = delete;
    TcpClient(const std::string& ip, const std::string& port) {
		 asio::io_service ios;
		asio::ip::tcp::resolver::query resolver_query(ip,
			port, asio::ip::tcp::resolver::query::numeric_service);
		asio::ip::tcp::resolver resolver(ios);
		asio::ip::tcp::resolver::iterator it =
			resolver.resolve(resolver_query);
		m_endpoint = it->endpoint();
		m_ip = m_endpoint.address().to_string();
		m_port = std::to_string(m_endpoint.port());
		m_name = m_ip + ':' + m_port;
	}

    Connection start() {
        asio::io_service ioService;
        asio::ip::tcp::socket socket(ioService);
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
	
	inline const std::string& getIp() const { return m_ip; }
	inline const std::string& getPort() const { return m_port; }
	inline const std::string& getName() const { return m_name; }
};

class TcpServer {
private:
    int m_port;

public:
	TcpServer(int port) : m_port(port) { }

	Connection accept() {
		asio::io_service ioService;
		asio::ip::tcp::acceptor acceptor(ioService, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), m_port));
		asio::ip::tcp::socket socket(ioService);
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
};
