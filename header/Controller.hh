#include <dzn/meta.hh>

namespace dzn {
  struct locator;
  struct runtime;
}



#include <iostream>
#include <map>

/********************************** INTERFACE *********************************/
#ifndef ICONTROLLER_HH
#define ICONTROLLER_HH




struct IController
{

  struct
  {
    std::function< void()> validPincode;
    std::function< void()> sensorTriggered;
  } in;

  struct
  {
  } out;

  dzn::port::meta meta;
  inline IController(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.validPincode) throw dzn::binding_error(meta, "in.validPincode");
    if (! in.sensorTriggered) throw dzn::binding_error(meta, "in.sensorTriggered");


  }
};

inline void connect (IController& provided, IController& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}





#endif // ICONTROLLER_HH

/********************************** INTERFACE *********************************/
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
/********************************** COMPONENT *********************************/
#ifndef CONTROLLER_HH
#define CONTROLLER_HH

#include "Timer.hh"
#include "ISiren.hh"
#include "ILED.hh"



struct Controller
{
  dzn::meta dzn_meta;
  dzn::runtime& dzn_rt;
  dzn::locator const& dzn_locator;
#ifndef ENUM_Controller_State
#define ENUM_Controller_State 1


  struct State
  {
    enum type
    {
      Unarmed,Armed,Alarming
    };
  };


#endif // ENUM_Controller_State

  ::Controller::State::type state;


  std::function<void ()> out_iController;

  ::IController iController;

  ::ITimer iTimer;
  ::ISiren iSiren;
  ::ILED iLed;


  Controller(const dzn::locator&);
  void check_bindings() const;
  void dump_tree(std::ostream& os) const;
  friend std::ostream& operator << (std::ostream& os, const Controller& m)  {
    (void)m;
    return os << "[" << m.state <<"]" ;
  }
  private:
  void iController_validPincode();
  void iController_sensorTriggered();
  void iTimer_timeout();

};

#endif // CONTROLLER_HH

/********************************** COMPONENT *********************************/


//version: 2.8.2
