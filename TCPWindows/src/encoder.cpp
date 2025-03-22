#include "encoder.h"

std::string Encoder::encode(std::string ip) {
	std::string temp = "";
	srand(time(NULL));
	Encoder::key = rand() % 26;
	Encoder::start = rand() % 26;

    Encoder::id += encodeMap[start];
    Encoder::id += encodeMap[(key + start) % 26];

    for (int i = 0; i < ip.size(); i++) {
        if (ip[i] == '.') {
            Encoder::id += encodeMap[(temp.size() + key) % 26];
            for (int j = 0; j < temp.size(); j++) {
                Encoder::id += encodeMap[(temp[j] - '0' + key) % 26];
            }
            temp.clear();
        }
        else {
            temp += ip[i];
        }
    }

    if (!temp.empty()) {
        Encoder::id += encodeMap[(temp.size() + key) % 26];
        for (int j = 0; j < temp.size(); j++) {
            Encoder::id += encodeMap[(temp[j] - '0' + key) % 26];
        }
    }
    return Encoder::id;
}

std::string Encoder::getPublicIPv4Address() {
		// Initialize Winsock
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
			return "Failed to initialize Winsock";
		}

		// Create a socket
		SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sock == INVALID_SOCKET) {
			WSACleanup();
			return "Socket creation failed";
		}

		// IP address lookup service
		std::string host = "api.ipify.org";
		std::string request = "GET / HTTP/1.1\r\nHost: " + host + "\r\nConnection: close\r\n\r\n";

		// Resolve the server address
		struct addrinfo hints = { 0 }, * result = NULL;
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		if (getaddrinfo(host.c_str(), "80", &hints, &result) != 0) {
			closesocket(sock);
			WSACleanup();
			return "Failed to resolve server address";
		}

		// Connect to the server
		if (connect(sock, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR) {
			freeaddrinfo(result);
			closesocket(sock);
			WSACleanup();
			return "Failed to connect to server";
		}

		freeaddrinfo(result);

		// Send the request
		if (send(sock, request.c_str(), (int)request.length(), 0) == SOCKET_ERROR) {
			closesocket(sock);
			WSACleanup();
			return "Failed to send request";
		}

		// Receive the response
		char buffer[4096];
		std::string response;
		int bytesReceived;

		while ((bytesReceived = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
			buffer[bytesReceived] = '\0';
			response += buffer;
		}

		// Clean up
		closesocket(sock);
		WSACleanup();

		// Extract IP address from the response
		// The response format from ipify is just the IP address as plain text
		size_t headerEnd = response.find("\r\n\r\n");
		if (headerEnd != std::string::npos) {
			std::string body = response.substr(headerEnd + 4);
			// Remove any trailing whitespace
			body.erase(body.find_last_not_of(" \n\r\t") + 1);
			return body;
		}

		return "Failed to parse response";
}
