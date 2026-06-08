#pragma once

#include <cstdint>

class Transmitter {
private:
    std::string data;
    uint16_t frameSize; // k bits

public:
    // Transmitter(uint16_t k);

    const std::string& getData() const;
    void setData(const std::string& data);

    std::vector<std::vector<uint16_t>> segmentFrame();
    // std::vector<std::vector<uint16_t>> crcFrame();
};
