#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>

// Frame
constexpr uint16_t PAYLOAD_BITS = 16;

// CRC
constexpr uint16_t CRC_BITS = 8;

// Channel
constexpr double BER = 0.01;

// HARQ
constexpr uint8_t MAX_RETX = 4;

// Simulation
constexpr uint32_t NUM_ITERATIONS = 1000;

#endif
