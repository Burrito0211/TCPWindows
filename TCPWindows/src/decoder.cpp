/*****************************************************************//**
 * \file   decoder.cpp
 * \brief  decoder's functions implement
 * 
 * \author B11315024 HAO-HSIN CHANG
 * \date   2025/3/22
 *********************************************************************/

#include "decoder.h"

int Decoder::getKey(char id, char id2) {
    int key = decodeMap[id];
    int ip = decodeMap[id2];
    if (key > ip) {
        return (ip - key + 26);
    }
    else {
        return (ip - key);
    }
}

int Decoder::reverse(int key, char id) {
    int ip = decodeMap[id];
    if (key > ip) return (ip - key + 26);
    return (ip - key);
}

std::string Decoder::decode(std::string id) {
    if (id.size() < 8) return ""; 

    int key = getKey(id[0], id[1]);
    std::string ip = "";
    int size = reverse(key, id[2]);
    int cur = 3;
    int ds = 0;
    for (int j = 0; j < 4; j++) {
        for (int i = cur; i < size + cur; i++) {
            ip += std::to_string(reverse(key, id[i]));
        }
        if (j < 3) {
            cur += size;
            ip += ".";
            size = reverse(key, id[cur]);
            cur++;
        }
    }
    return ip;
}
