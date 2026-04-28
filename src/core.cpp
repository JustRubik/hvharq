#include "core.h"

Core::Core(){};
// Core::Core() : input(""), output(""), check(true) {}; 

void Core::checkReliability () {
    check = (input == output) ? true : false;
}
