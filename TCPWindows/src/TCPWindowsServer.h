// TCPWindowsServer.h: 標準系統 include 檔案的 include 檔案，
// 或專案專屬的 Include 檔案。

#pragma once

#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include "encoder.h"

#pragma comment (lib, "ws2_32.lib")

class Server {
public:
	int startServer();
	bool sendMessage(SOCKET s, const char* buf, int size);
private:
};

// TODO: 在此參考您的程式所需的其他標頭。
