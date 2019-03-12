#include "LED.hh"

#include <iostream>

LED::LED(const dzn::locator &loc) : skel::LED(loc) {
    std::cout << "LED is constructed!" << std::endl;
}

void LED::iLed_setGreen() {
    std::cout << "LED is set to Green!" << std::endl;
}

void LED::iLed_setRed() {
    std::cout << "LED is set to Red!" << std::endl;
}

void LED::iLed_setYellow() {
    std::cout << "LED is set to Yellow!" << std::endl;
}

void  LED::iLed_turnOff() {
    std::cout << "LED is turned off!" << std::endl;
}