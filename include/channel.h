#pragma once

#include <stdint.h>
#include <string>
#include <random>

#include "..\include\config.h"

//  Channel -> kenh truyen
class Channel
{
private:
  double ber;
  std::mt19937 gen;
  std::bernoulli_distribution error;

public:
  Channel(double p = BER)
      : ber(p),
        gen(std::random_device{}()),
        error(p)
  {
  }

  Frame transmit(const Frame &frame);
};
