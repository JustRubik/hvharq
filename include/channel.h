#pragma once

#include <stdint.h>
#include <string>

//  Channel -> kenh truyen

class Channel {
  private:
    double BER;
  public:
    std::string transmit(const std::string& frame);
};
