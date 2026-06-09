#include "..\include\helper.h"

#include <iostream>

std::vector<uint8_t> Helper::stringToBits(const std::string& str)
{
    std::vector<uint8_t> bits;

    for (unsigned char c : str)
    {
        for (int i = 7; i >= 0; --i)
        {
            bits.push_back((c >> i) & 1);
        }
    }

    return bits;
}

std::string Helper::bitsToString(const std::vector<uint8_t>& bits)
{
    std::string result;

    if (bits.size() % 8 != 0)
    {
        return result;
    }

    for (size_t i = 0; i < bits.size(); i += 8)
    {
        uint8_t byte = 0;

        for (int j = 0; j < 8; ++j)
        {
            byte = (byte << 1) | bits[i + j];
        }

        result.push_back(static_cast<char>(byte));
    }

    return result;
}

void Helper::printBits(const std::vector<uint8_t>& bits)
{
    for (uint8_t bit : bits)
    {
        std::cout << static_cast<int>(bit);
    }

    std::cout << '\n';
}

uint8_t Helper::xorBits(const std::vector<uint8_t>& bits)
{
    uint8_t result = 0;

    for (uint8_t bit : bits)
    {
        result ^= bit;
    }

    return result;
}
