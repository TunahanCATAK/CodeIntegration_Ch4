#include "Siren.hh"

#include <iostream>

Siren::Siren(const dzn::locator &loc) : skel::Siren(loc){
    std::cout << "Siren is constructed." << std::endl;
}


void Siren::iSiren_turnOff() {
    std::cout << "Siren is turned off." << std::endl;
}

void Siren::iSiren_turnOn() {
    std::cout << "Siren is turned on." << std::endl;
}