#include <iostream>
#include <vector>

#include "../include/transmitter.h"
#include "../include/config.h"

using Bit = uint8_t;
using Frame = std::vector<Bit>;

int main()
{
    Transmitter tx;
    tx.setData("HIEURUBIK");

    std::vector<std::vector<uint8_t>> frames = tx.segmentFrame();

    std::cout << "Number of frames: "
              << frames.size()
              << "\n\n";

    for (size_t i = 0; i < frames.size(); ++i)
    {
        std::cout << "Frame " << i << ": ";

        for (Bit bit : frames[i])
        {
            std::cout << static_cast<int>(bit);
        }

        std::cout << '\n';
    }

    std::vector<std::vector<uint8_t>> crcFrame = tx.CRC(frames);

    for (size_t i = 0; i < crcFrame.size(); ++i)
    {
        std::cout << "CRCFrame " << i << ": ";

        for (Bit bit : crcFrame[i])
        {
            std::cout << static_cast<int>(bit);
        }

        std::cout << '\n';
    }

    std::vector<std::vector<uint8_t>> ccFrame = tx.convolutionEncode(crcFrame);

    for (size_t i = 0; i < ccFrame.size(); ++i)
    {
        std::cout << "ConvolutionCodeFrame " << i << ": ";

        for (Bit bit : ccFrame[i])
        {
            std::cout << static_cast<int>(bit);
        }

        std::cout << '\n';
    }

    std::cout << "Data là " << tx.getData() << std::endl;

    return 0;
}



