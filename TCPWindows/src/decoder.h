/*****************************************************************//**
 * \file   decoder.h
 * \brief  decoder
 * 
 * \author B11315024 HAO-HSIN CHANG
 * \date   2025/3/22
 *********************************************************************/

#pragma once
#include <map>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <map>

class Decoder {
public:
	int reverse(int key, char id);
	int getKey(char id, char id2);
	std::string decode(std::string id);
private:
	std::map<char, int> decodeMap = {
		{'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}, {'E', 4}, {'F', 5}, {'G', 6}, {'H', 7}, {'I', 8}, {'J', 9},
		{'K', 10}, {'L', 11}, {'M', 12}, {'N', 13}, {'O', 14}, {'P', 15}, {'Q', 16}, {'R', 17}, {'S', 18}, {'T', 19},
		{'U', 20}, {'V', 21}, {'W', 22}, {'X', 23}, {'Y', 24}, {'Z', 25}
	};
};
