# CMakeList.txt: TCPWindowsClient 的 CMake 專案，在此包含來源及定義
# 專案專屬邏輯。
#
cmake_minimum_required (VERSION 3.8)
project(TCPWindows)

# 將來源新增到此專案的可執行檔。
add_executable (TCPWindowsClient 
		src/TCPWindowsClient.cpp src/TCPWindowsClient.h 
		src/TCPWindowsServer.cpp src/TCPWindowsServer.h
		src/decoder.h src/decoder.cpp
		src/encoder.h src/encoder.cpp
		src/main.cpp)

# TODO: 新增測試，並視需要安裝目標。
