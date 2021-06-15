#pragma once 

#include <asio.hpp>
#include <iostream>
#include <vector>
#include <thread>
#include <string>

class Connection {
private:
    asio::ip::tcp::socket m_socket;
	bool m_alive;

public:
    Connection() = delete;
    Connection(const Connection& other) = delete;
    Connection(asio::ip::tcp::socket socket) : m_socket(std::move(socket)), m_alive(true) { }
    Connection(Connection&& other) : m_socket(std::move(other.m_socket)), m_alive(other.m_alive) { }

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
    
    inline bool isActive() const { return m_alive; }
	inline std::string getName() const { return m_socket.remote_endpoint().address().to_string(); }
	inline void terminate() {
		if (!m_alive) {
			return;
		}
		m_alive = false;
		try {
			m_socket.close();
		}
		catch (const std::exception& e) { }
	}
};

class TcpClient {
	std::string m_ip;
	int m_port;
    
public:
    TcpClient() = delete;
    TcpClient(const TcpClient& other) = delete;
    TcpClient(std::string ip, int port) : m_ip(ip), m_port(port) { }

    Connection start() {
		 asio::io_service ios;

		asio::ip::tcp::resolver::query resolver_query(m_ip,
			std::to_string(m_port), asio::ip::tcp::resolver::query::numeric_service);
		asio::ip::tcp::resolver resolver(ios);
		asio::ip::tcp::resolver::iterator it =
			resolver.resolve(resolver_query);

        asio::io_service ioService;
        asio::ip::tcp::socket socket(ioService);
		try {
        	socket.connect(it->endpoint());
		}
		catch (const std::exception& e) { 
			Connection c(std::move(socket));
			c.terminate();
			return std::move(c);
		}
        return Connection(std::move(socket));
    }
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
		acceptor.accept(socket);
		return Connection(std::move(socket));
	}
};
