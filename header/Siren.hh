#include "ISiren.hh"

class Siren : public skel::Siren{
    void iSiren_turnOn ();
    void iSiren_turnOff ();


public:
    Siren(const dzn::locator& loc);
};