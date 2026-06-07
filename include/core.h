#pragma once

#include <string>

//  Global vars


// Description: Main simulation engine for arq/harq transmission.

class Core {
    private:
        std::string input = "";
        std::string output = "";
        bool check = true;
    public:
        Core();
        ~Core();
        // void checkReliability();
        void encoder();
        void decoder();
        void convolutionCode();
        void runarq();
        void runharq();
};
