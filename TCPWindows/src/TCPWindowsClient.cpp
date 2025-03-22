/*****************************************************************//**
 * \file   Source.cpp
 * \brief  Client main cpp
 *
 * \author B11315024 HAO-HSIN CHANG
 * \date   2025/3/21
 *********************************************************************/

#include "TCPWindowsClient.h"

int Client::startClient() {
	Decoder decode;
	std::string ipAddress = "";   // IP address of the server
	std::string userInput = "";
	int port = 54000;                      // Listening port on the server

	std::cout << "Please enter the room ID: ";
	std::getline(std::cin, ipAddress);
	ipAddress = decode.decode(ipAddress);

	while (true) {
		if (isValidIPv4(ipAddress)) {
			break;
		}
		else {
			system("cls");
			std::cout << "Not a valid room ID! Please enter again: ";
			std::getline(std::cin, ipAddress);
			ipAddress = decode.decode(ipAddress);
		}
	}

	// Initialize Winsock
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0) {
		std::cerr << "Can't start Winsock, Err" << wsResult << std::endl;
		return 1;
	}

	// Create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		std::cerr << "Can't create socket, Err #" << WSAGetLastError << std::endl;
		return 1;
	}

	// Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	// Connect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));

	// Keep prompting user to enter IP until connect successfully
	while (connResult == SOCKET_ERROR) {
		system("cls");
		std::cerr << "Can't connect to server, Err #" << WSAGetLastError << std::endl;
		std::cout << "Please enter the room ID: ";
		std::getline(std::cin, ipAddress);
		ipAddress = decode.decode(ipAddress);

		hint.sin_family = AF_INET;
		hint.sin_port = htons(port);
		inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

		// Connect to server
		connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	}

	// Do-while loop to sesnd and receive data
	char buf[4096];

	std::cout << "Please enter your name: ";
	std::getline(std::cin, userInput);
	send(sock, userInput.c_str(), userInput.size() + 1, 0);
	int bytesReceived = recv(sock, buf, 4096, 0);

	while (std::string(buf, 0, 3) != "ok") {
		system("cls");
		std::cout << "Connecting to server .";
		for (int i = 0; i < 2; i++) {
			Sleep(50);
			std::cout << ". ";
		}
	}

	std::cout << "Connected successfully!" << std::endl;

	do {
		// Prompt the user for some text
		std::cout << "Input your message here: ";
		std::getline(std::cin, userInput);

		if (userInput.size() > 0) {
			// Send the text
			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
			if (sendResult != SOCKET_ERROR) {
				// Wait for response
				ZeroMemory(buf, 4096);
				bytesReceived = recv(sock, buf, 4096, 0);
				if (bytesReceived > 0) {
					// Echo response to console
					std::cout << "SERVER: " << std::string(buf, 0, bytesReceived) << std::endl;
					if (std::string(buf, 0, bytesReceived) == "close") break;
				}
			}
		}

	} while (userInput != "close");

	// Gracefully close down everything
	closesocket(sock);
	WSACleanup();


}


bool Client::isValidIPv4(const std::string& ip) {
	const std::regex pattern(
		"^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
		"(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
		"(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
		"(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$"
	);

	return std::regex_match(ip, pattern);
}

Client::~Client()
{
}
