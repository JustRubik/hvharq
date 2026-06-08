#pragma once

#include <stdint.h>
#include <string>

class Transmitter {
  private: 
    std::string data; // data truyen
    uint8_t buffer; // 3 bits
  public:
    Transmitter();
    ~Transmitter(); 
    std::string getData();  // getter
    void setData();         // setter
    void CRC_Encoder(); // ma hoa crc
    void FEC_Encoder(); // ma hoa fec
    void timer(); // set timeout
};

