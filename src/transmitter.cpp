#include "transmitter.h"
#include "config.h"
#include "helper.h"

const std::string& Transmitter::getData() const {
  return data;
}

void Transmitter::setData(const std::string& data){
  this->data = data;
}

std::vector<std::vector<uint16_t>> Transmitter::segmentFrame()
{
    std::vector<uint16_t> bits =
        Helper::stringToBits(data);

    std::vector<std::vector<uint16_t>> frames;

    for (size_t i = 0; i < bits.size(); i += frameSize)
    {
        std::vector<uint16_t> frame;

        for (size_t j = i;
             j < i + frameSize && j < bits.size();
             ++j)
        {
            frame.push_back(bits[j]);
        }

        // padding frame cuối nếu thiếu
        while (frame.size() < frameSize)
        {
            frame.push_back(0);
        }

        frames.push_back(frame);
    }

    return frames;
}

std::vector<std::vector<uint16_t>> crcFrame() {
  
}
