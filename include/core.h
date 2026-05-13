#pragma once

#include <string>

// Description: Core is a class which presenting the channel coding of the system, with input is a string that the transmitter transmits to the receiver through the channel and output is a string that the receiver receives, and they may be different from the other and vice versa.
// Nói chung là, comment hơi dài

class Core {
    private:
        std::string input = "";
        std::string output = "";
        bool check = true;
    public:
        Core();
        ~Core();
        void checkReliability();
};
