#include <dzn/meta.hh>

namespace dzn {
  struct locator;
  struct runtime;
}



#include <iostream>
#include <map>

/********************************** INTERFACE *********************************/
#ifndef ISIREN_HH
#define ISIREN_HH




struct ISiren
{

  struct
  {
    std::function< void()> turnOn;
    std::function< void()> turnOff;
  } in;

  struct
  {
  } out;

  dzn::port::meta meta;
  inline ISiren(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.turnOn) throw dzn::binding_error(meta, "in.turnOn");
    if (! in.turnOff) throw dzn::binding_error(meta, "in.turnOff");


  }
};

inline void connect (ISiren& provided, ISiren& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}





#endif // ISIREN_HH

/********************************** INTERFACE *********************************/
/***********************************  FOREIGN  **********************************/
#ifndef SKEL_SIREN_HH
#define SKEL_SIREN_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>




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


//version: 2.8.2
