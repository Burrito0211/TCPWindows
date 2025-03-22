/*****************************************************************//**
 * \file   TCPWindowsTest.cpp
 * \brief  Server main cpp
 *
 * \author B11315024 HAO-HSIN CHANG
 * \date   2025/3/21
 *********************************************************************/

#include "TCPWindowsServer.h"


int Server::startServer() {
	// Implement of the encoder
	Encoder encoder;
	// To store the user's ip address
	std::string ip;

	// Encode user's ip into room ID
	ip = encoder.encode(encoder.getPublicIPv4Address());
	std::cout << "Your room ID: " << ip << std::endl;

	// Initial winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0) {
		std::cerr << "Can't Initialize winsock! Quitting" << std::endl;
		return 1;
	}

	// Create socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET) {
		std::cerr << "Can't create a socket! Quitting" << std::endl;
		return 1;
	}

	// Bind the ip address and port to a socket  
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	// Tell winsock the socket is for listening
	listen(listening, SOMAXCONN);

	// Wait for a connection
	sockaddr_in client;
	int clientSize = sizeof(client);

	std::cout << "Waiting for connections." << std::endl;
	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

	if (clientSocket == INVALID_SOCKET) {
		std::cerr << "ERROR!" << std::endl;
		return 1;
	}

	char host[NI_MAXHOST];       // Client's remote name 
	char service[NI_MAXHOST];    // Service (port) the client is connect on

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXHOST);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
		std::cout << host << " connected on port " << service << std::endl;
	}
	else {
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		std::cout << host << " connected on port " << ntohs(client.sin_port) << std::endl;
	}

	// Close listening socket
	closesocket(listening);

	// Initialize buf into ok
	char buf[4096] = "ok";

	// Sent ok to client once connected
	send(clientSocket, buf, 3, 0);

	// Receive the client's name 
	int size = recv(clientSocket, buf, 4096, 0);
	std::cout << "Name: " << std::string(buf, 0, size) << std::endl;

	// While loop: acept and echo message back to client
	while (true) {
		ZeroMemory(buf, 4096);

		// Wait for client to sent data
		int bytesReceived = recv(clientSocket, buf, 4096, 0);

		if (bytesReceived == SOCKET_ERROR) {
			std::cerr << "Error in recv(). Quitting" << std::endl;
			break;
		}

		// If client send "close", close the server
		if (std::string(buf, 0, bytesReceived + 1) == "close") {
			std::cout << "Client disconnected" << std::endl;
			break;
		}

		// Echo message back to client
		// If input message is "close", break
		if (!sendMessage(clientSocket, buf, bytesReceived)) break;

	}
	// Close the socket
	closesocket(clientSocket);

	// Shutdown winsock
	WSACleanup();

	return 0;
}

bool Server::sendMessage(SOCKET s, const char* buf, int size) {
	std::string input = std::string(buf, 0, size);

	std::cout << "Client: " << input << std::endl;
	std::string output;
	std::cout << "Input your words here: ";
	std::getline(std::cin, output);

	send(s, output.c_str(), output.size() + 1, 0);

	return output == "close" ? false : true;
}



