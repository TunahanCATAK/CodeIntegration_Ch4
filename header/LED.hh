#include "ILED.hh"

class LED: public skel::LED {
    void iLed_setGreen ();
    void iLed_setYellow ();
    void iLed_setRed ();
    void iLed_turnOff ();

public:
    LED(const dzn::locator& loc);

};