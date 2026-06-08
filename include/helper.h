#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <vector>
#include <cstdint>

class Helper {
public:
    // String <-> Bitstream
    static std::vector<uint8_t> stringToBits(const std::string& str);
    static std::string bitsToString(const std::vector<uint8_t>& bits);

    // Debug
    static void printBits(const std::vector<uint8_t>& bits);

    // Utility
    static uint8_t xorBits(const std::vector<uint8_t>& bits);


};

// typedef struct Frame {
//   uint8_t id;
//   std::vector<uint8_t> payload;
// };

#endif
