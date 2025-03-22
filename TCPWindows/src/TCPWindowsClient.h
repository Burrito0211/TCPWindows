// TCPWindowsClient.h: 標準系統 include 檔案的 include 檔案，
// 或專案專屬的 Include 檔案。

#pragma once

#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include <regex>
#include <windows.h>

#include "decoder.h"

#pragma comment (lib, "ws2_32.lib")

class Client {
public:
	bool isValidIPv4(const std::string& ip);
	int startClient();
	~Client();
private:
};


// TODO: 在此參考您的程式所需的其他標頭。
