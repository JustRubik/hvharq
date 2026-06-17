#include <iostream>
#include <vector>

#include "../include/sender.h"
#include "../include/config.h"
#include "../include/helper.h"

int main()
{
    Sender sd;
    sd.setData("HIEURUBIK");

    std::vector<std::vector<uint8_t>> frames = sd.segmentFrame();

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

    std::vector<std::vector<uint8_t>> crcFrame = sd.CRC(frames);

    for (size_t i = 0; i < crcFrame.size(); ++i)
    {
        std::cout << "CRCFrame " << i << ": ";

        for (Bit bit : crcFrame[i])
        {
            std::cout << static_cast<int>(bit);
        }

        std::cout << '\n';
    }

    std::vector<std::vector<uint8_t>> ccFrame = sd.convolutionEncode(crcFrame);

    for (size_t i = 0; i < ccFrame.size(); ++i)
    {
        std::cout << "ConvolutionCodeFrame " << i << ": ";

        for (Bit bit : ccFrame[i])
        {
            std::cout << static_cast<int>(bit);
        }

        std::cout << '\n';
    }

    std::cout << "Data là " << sd.getData() << std::endl;

    return 0;
}
