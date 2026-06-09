#pragma once

#include <string>
#include <cstdint>
#include <vector>

#include "..\include\config.h"
#include "..\include\helper.h"

enum State
{
    sending = 0,
    waiting,
    ACKed
};

class Transmitter
{
private:
    std::string data = "";
    struct Buffer
    {      
        State state = waiting;
        uint8_t retx_count = 0;
        std::vector<uint8_t> frames;
    };

public:
    const std::string &getData() const;
    void setData(const std::string &data);

    std::vector<std::vector<uint8_t>> segmentFrame();
    std::vector<std::vector<uint8_t>> CRC(std::vector<std::vector<uint8_t>> &input);
    std::vector<std::vector<uint8_t>> convolutionEncode
        (std::vector<std::vector<uint8_t>> &input);
};
