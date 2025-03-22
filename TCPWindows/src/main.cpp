/*****************************************************************//**
 * \file   main.cpp
 * \brief  main function
 * 
 * \author B11315024 HAO-HSIN CHANG
 * \date   2025/3/22
 *********************************************************************/

#include "TCPWindowsClient.h"
#include "TCPWindowsServer.h"

int main() {
	Client client;
	Server server;

	std::string input ="";
	while (1) {
		if (input == "client") {
			client.startClient();
			break;
		}
		else if (input == "server") {
			server.startServer();
			break;
		}
		else {
			std::cout << "Please enter \"client\" or \"server\" to start them: ";
			std::getline(std::cin, input);
		}
	}

	return 0;
}
