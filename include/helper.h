#pragma once

#include <string>
#include <vector>
#include <cstdint>

#include "..\include\config.h"

class Helper
{
public:
    // String <-> Bitstream
    static std::vector<uint8_t> stringToBits(const std::string &str);
    static std::string bitsToString(const Frame &bits);

    // Debug
    static void printBits(const Frame &bits);

    // Utility
    static uint8_t xorBits(const Frame &bits);

    static uint8_t computeCRC8(const Frame &bits);
};
