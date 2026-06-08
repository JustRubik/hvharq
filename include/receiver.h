#pragma once

#include <stdint.h>
#include <string>

class Receiver {
  private: 
    std::string data; // data nhan duoc
    // uint8_t buffer; // 3 bits
  public:
    // Receiver();
    // ~Receiver(); 
    std::string getData();  // getter
    void setData();         // setter
    void CRC_Decoder(); // giai ma crc
    void FEC_Decoder(); // giai ma fec
    void checkCRC();  // kiem tra bit crc du
    void acknowledgement(); // tra ve ack hoac nak
    // void timer();
};

