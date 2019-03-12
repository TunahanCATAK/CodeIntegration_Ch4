#include <dzn/meta.hh>

namespace dzn {
  struct locator;
  struct runtime;
}



#include <iostream>
#include <map>

/********************************** INTERFACE *********************************/
#ifndef IPWDMANAGER_HH
#define IPWDMANAGER_HH




struct IPwdManager
{

  struct
  {
    std::function< bool(std::string pwd)> verifyPassword;
  } in;

  struct
  {
  } out;

  dzn::port::meta meta;
  inline IPwdManager(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.verifyPassword) throw dzn::binding_error(meta, "in.verifyPassword");


  }
};

inline void connect (IPwdManager& provided, IPwdManager& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}





#endif // IPWDMANAGER_HH

/********************************** INTERFACE *********************************/
/***********************************  FOREIGN  **********************************/
#ifndef SKEL_PWDMANAGER_HH
#define SKEL_PWDMANAGER_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>




namespace skel {
  struct PwdManager
  {
    dzn::meta dzn_meta;
    dzn::runtime& dzn_rt;
    dzn::locator const& dzn_locator;
    ::IPwdManager iPwdManager;


    PwdManager(const dzn::locator& dzn_locator)
    : dzn_meta{"","PwdManager",0,0,{},{},{[this]{iPwdManager.check_bindings();}}}
    , dzn_rt(dzn_locator.get<dzn::runtime>())
    , dzn_locator(dzn_locator)

    , iPwdManager({{"iPwdManager",this,&dzn_meta},{"",0,0}})


    {

      iPwdManager.in.verifyPassword = [&](std::string pwd){return dzn::call_in(this,[=]{ return iPwdManager_verifyPassword(pwd);}, this->iPwdManager.meta, "verifyPassword");};

    }
    virtual ~ PwdManager() {}
    virtual std::ostream& stream_members(std::ostream& os) const { return os; }
    void check_bindings() const;
    void dump_tree(std::ostream& os) const;
    void set_state(std::map<std::string,std::map<std::string,std::string> >){}
    void set_state(std::map<std::string,std::string>_alist){}
    friend std::ostream& operator << (std::ostream& os, const PwdManager& m)  {
      return m.stream_members(os);
    }
    private:
    virtual bool iPwdManager_verifyPassword (std::string pwd) = 0;

  };
}

#endif // PWDMANAGER_HH

/***********************************  FOREIGN  **********************************/


//version: 2.8.2
