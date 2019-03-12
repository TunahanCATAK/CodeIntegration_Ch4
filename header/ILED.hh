#include <dzn/meta.hh>

namespace dzn {
  struct locator;
  struct runtime;
}



#include <iostream>
#include <map>

/********************************** INTERFACE *********************************/
#ifndef ILED_HH
#define ILED_HH




struct ILED
{

  struct
  {
    std::function< void()> setGreen;
    std::function< void()> setYellow;
    std::function< void()> setRed;
    std::function< void()> turnOff;
  } in;

  struct
  {
  } out;

  dzn::port::meta meta;
  inline ILED(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.setGreen) throw dzn::binding_error(meta, "in.setGreen");
    if (! in.setYellow) throw dzn::binding_error(meta, "in.setYellow");
    if (! in.setRed) throw dzn::binding_error(meta, "in.setRed");
    if (! in.turnOff) throw dzn::binding_error(meta, "in.turnOff");


  }
};

inline void connect (ILED& provided, ILED& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}





#endif // ILED_HH

/********************************** INTERFACE *********************************/
/***********************************  FOREIGN  **********************************/
#ifndef SKEL_LED_HH
#define SKEL_LED_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>




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


//version: 2.8.2
