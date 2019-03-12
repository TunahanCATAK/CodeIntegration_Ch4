#include "AlarmSystem.hh"

#include <dzn/locator.hh>
#include <dzn/runtime.hh>


//SYSTEM

AlarmSystem::AlarmSystem(const dzn::locator& dzn_locator)
: dzn_meta{"","AlarmSystem",0,0,{& iTimer.meta},{& controller.dzn_meta,& led.dzn_meta,& siren.dzn_meta,& pManager.dzn_meta},{[this]{iController.check_bindings();},[this]{iTimer.check_bindings();}}}
, dzn_rt(dzn_locator.get<dzn::runtime>())
, dzn_locator(dzn_locator)


, controller(dzn_locator)
, led(dzn_locator)
, siren(dzn_locator)
, pManager(dzn_locator)

, iController(controller.iController)
, iTimer(controller.iTimer)
{


  controller.dzn_meta.parent = &dzn_meta;
  controller.dzn_meta.name = "controller";
  led.dzn_meta.parent = &dzn_meta;
  led.dzn_meta.name = "led";
  siren.dzn_meta.parent = &dzn_meta;
  siren.dzn_meta.name = "siren";
  pManager.dzn_meta.parent = &dzn_meta;
  pManager.dzn_meta.name = "pManager";


  connect(led.iLed, controller.iLed);
  connect(siren.iSiren, controller.iSiren);
  connect(pManager.iPwdManager, controller.iPwdManager);

  dzn::rank(iController.meta.provides.meta, 0);

}

void AlarmSystem::check_bindings() const
{
  dzn::check_bindings(&dzn_meta);
}
void AlarmSystem::dump_tree(std::ostream& os) const
{
  dzn::dump_tree(os, &dzn_meta);
}

////////////////////////////////////////////////////////////////////////////////



//version: 2.8.2