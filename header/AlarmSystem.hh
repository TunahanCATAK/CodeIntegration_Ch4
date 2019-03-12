#include <dzn/meta.hh>

namespace dzn {
  struct locator;
  struct runtime;
}



#include <iostream>
#include <map>

/***********************************  FOREIGN  **********************************/
#ifndef SKEL_LED_HH
#define SKEL_LED_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>

#include "ILED.hh"



namespace skel {
  struct LED
  {
    dzn::meta dzn_meta;
    dzn::runtime& dzn_rt;
    dzn::locator const& dzn_locator;
    ::ILED iLed;


    LED(const dzn::locator& dzn_locator)
    : dzn_meta{"","LED",0,0,{},{},{[this]{iLed.check_bindings();}}}
    , dzn_rt(dzn_locator.get<dzn::runtime>())
    , dzn_locator(dzn_locator)

    , iLed({{"iLed",this,&dzn_meta},{"",0,0}})


    {
      iLed.in.setGreen = [&](){return dzn::call_in(this,[=]{ return iLed_setGreen();}, this->iLed.meta, "setGreen");};
      iLed.in.setYellow = [&](){return dzn::call_in(this,[=]{ return iLed_setYellow();}, this->iLed.meta, "setYellow");};
      iLed.in.setRed = [&](){return dzn::call_in(this,[=]{ return iLed_setRed();}, this->iLed.meta, "setRed");};
      iLed.in.turnOff = [&](){return dzn::call_in(this,[=]{ return iLed_turnOff();}, this->iLed.meta, "turnOff");};


    }
    virtual ~ LED() {}
    virtual std::ostream& stream_members(std::ostream& os) const { return os; }
    void check_bindings() const;
    void dump_tree(std::ostream& os) const;
    void set_state(std::map<std::string,std::map<std::string,std::string> >){}
    void set_state(std::map<std::string,std::string>_alist){}
    friend std::ostream& operator << (std::ostream& os, const LED& m)  {
      return m.stream_members(os);
    }
    private:
    virtual void iLed_setGreen () = 0;
    virtual void iLed_setYellow () = 0;
    virtual void iLed_setRed () = 0;
    virtual void iLed_turnOff () = 0;

  };
}

#endif // LED_HH

/***********************************  FOREIGN  **********************************/
/***********************************  FOREIGN  **********************************/
#ifndef SKEL_SIREN_HH
#define SKEL_SIREN_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>

#include "ISiren.hh"



namespace skel {
  struct Siren
  {
    dzn::meta dzn_meta;
    dzn::runtime& dzn_rt;
    dzn::locator const& dzn_locator;
    ::ISiren iSiren;


    Siren(const dzn::locator& dzn_locator)
    : dzn_meta{"","Siren",0,0,{},{},{[this]{iSiren.check_bindings();}}}
    , dzn_rt(dzn_locator.get<dzn::runtime>())
    , dzn_locator(dzn_locator)

    , iSiren({{"iSiren",this,&dzn_meta},{"",0,0}})


    {
      iSiren.in.turnOn = [&](){return dzn::call_in(this,[=]{ return iSiren_turnOn();}, this->iSiren.meta, "turnOn");};
      iSiren.in.turnOff = [&](){return dzn::call_in(this,[=]{ return iSiren_turnOff();}, this->iSiren.meta, "turnOff");};


    }
    virtual ~ Siren() {}
    virtual std::ostream& stream_members(std::ostream& os) const { return os; }
    void check_bindings() const;
    void dump_tree(std::ostream& os) const;
    void set_state(std::map<std::string,std::map<std::string,std::string> >){}
    void set_state(std::map<std::string,std::string>_alist){}
    friend std::ostream& operator << (std::ostream& os, const Siren& m)  {
      return m.stream_members(os);
    }
    private:
    virtual void iSiren_turnOn () = 0;
    virtual void iSiren_turnOff () = 0;

  };
}

#endif // SIREN_HH

/***********************************  FOREIGN  **********************************/
/***********************************  SYSTEM  ***********************************/
#ifndef ALARMSYSTEM_HH
#define ALARMSYSTEM_HH


#include <dzn/locator.hh>

#include "Controller.hh"
#include "LED.hh"
#include "Siren.hh"



struct AlarmSystem
{
  dzn::meta dzn_meta;
  dzn::runtime& dzn_rt;
  dzn::locator const& dzn_locator;


  ::Controller controller;
  ::LED led;
  ::Siren siren;

  ::IController& iController;

  ::ITimer& iTimer;

  AlarmSystem(const dzn::locator&);
  void check_bindings() const;
  void dump_tree(std::ostream& os=std::clog) const;
};

#endif // ALARMSYSTEM_HH

/***********************************  SYSTEM  ***********************************/


//version: 2.8.2
