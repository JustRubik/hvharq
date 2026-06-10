#include "..\include\sender.h"
#include "..\include\config.h"
#include "..\include\helper.h"

const std::string &Sender::getData() const
{
    return data;
}

void Sender::setData(const std::string &data)
{
    this->data = data;
}

std::vector<Frame> Sender::segmentFrame()
{
    std::vector<Bit> bits =
        Helper::stringToBits(this->data);

    std::vector<Frame> frames;

    size_t s = bits.size(); // thay đổi theo vòng lặp

    for (size_t i = 0; i < s; i += PAYLOAD_BITS)
    {
        Frame frame;

        size_t limit = (PAYLOAD_BITS < s - i) ? PAYLOAD_BITS : s - i;

        for (size_t j = 0; j < limit; ++j)
        {
            frame.push_back(bits[i + j]);
        }

        frames.push_back(frame);
    }

    return frames;
}

std::vector<Frame> Sender::CRC(std::vector<Frame> &frames)
{
    for (Frame &frame : frames)
    {
        uint8_t crc = Helper::computeCRC8(frame);

        for (int i = 7; i >= 0; --i)
        {
            frame.push_back((crc >> i) & 1);
        }
    }

    return frames;
}

Frame convolutionEncodePerFrame(Frame &input)
{
    Frame output;

    uint8_t shift_reg = 0; // 3-bit state (we'll use lower 3 bits)

    for (Bit bit : input)
    {
        bit &= 1;

        // shift register update
        shift_reg = ((shift_reg << 1) | bit) & 0x07; // keep 3 bits

        // extract bits
        Bit m0 = (shift_reg >> 0) & 1;
        Bit m1 = (shift_reg >> 1) & 1;
        Bit m2 = (shift_reg >> 2) & 1;

        // generator 1: 111
        Bit y1 = m0 ^ m1 ^ m2;

        // generator 2: 101
        Bit y2 = m0 ^ m2;

        output.push_back(y1);
        output.push_back(y2);
    }

    return output;
}

std::vector<Frame> Sender::convolutionEncode(std::vector<Frame> &input)
{
    std::vector<Frame> output;
    output.reserve(input.size());

    for (Frame &frame : input)
    {
        output.push_back(convolutionEncodePerFrame(frame));
    }

    return output;
}
