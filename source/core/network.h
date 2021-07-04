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
	Connection(asio::ip::tcp::socket socket,
		const std::string& name,
		const std::string& ip,
		const std::string& port);
	Connection(Connection&& other);

	Connection& operator=(Connection other);
	std::string read();
	bool send(const std::string& message);
	void terminate();
    
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
	TcpClient(const std::string& ip, const std::string& port);

	Connection start();
	
	inline const std::string& getIp() const { return m_ip; }
	inline const std::string& getPort() const { return m_port; }
	inline const std::string& getName() const { return m_name; }
};

class TcpServer {
private:
    int m_port;

public:
	TcpServer() = delete;
	TcpServer(int port) : m_port(port) { }

	Connection accept();
};
