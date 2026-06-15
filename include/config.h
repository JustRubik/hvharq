#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>
#include <vector>

using Bit = uint8_t;
using Frame = std::vector<Bit>;

// Frame
constexpr uint16_t PAYLOAD_BITS = 128;

// CRC
constexpr uint16_t CRC_BITS = 8;

constexpr uint16_t FRAME_SIZE = PAYLOAD_BITS + CRC_BITS; // default = 64 + 8

// Channel
constexpr double BER = 0.01;

// HARQ
constexpr uint8_t MAX_RETX = 15;

// Simulation
constexpr uint32_t NUM_ITERATIONS = 1000;

constexpr uint8_t G = 0b00000111; // đa thức sinh, = 0x07

#endif
