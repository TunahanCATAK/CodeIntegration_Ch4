#include "Controller.hh"

#include <dzn/locator.hh>
#include <dzn/runtime.hh>



Controller::Controller(const dzn::locator& dzn_locator)
: dzn_meta{"","Controller",0,0,{& iTimer.meta,& iSiren.meta,& iLed.meta,& iPwdManager.meta},{},{[this]{iController.check_bindings();},[this]{iTimer.check_bindings();},[this]{iSiren.check_bindings();},[this]{iLed.check_bindings();},[this]{iPwdManager.check_bindings();}}}
, dzn_rt(dzn_locator.get<dzn::runtime>())
, dzn_locator(dzn_locator)
, state(::Controller::State::Unarmed)

, iController({{"iController",this,&dzn_meta},{"",0,0}})

, iTimer({{"",0,0},{"iTimer",this,&dzn_meta}})
, iSiren({{"",0,0},{"iSiren",this,&dzn_meta}})
, iLed({{"",0,0},{"iLed",this,&dzn_meta}})
, iPwdManager({{"",0,0},{"iPwdManager",this,&dzn_meta}})


{
  dzn_rt.performs_flush(this) = true;

  iController.in.passwordEnterred = [&](std::string pwd){return dzn::call_in(this,[=]{ return iController_passwordEnterred(pwd);}, this->iController.meta, "passwordEnterred");};
  iController.in.sensorTriggered = [&](){return dzn::call_in(this,[=]{ return iController_sensorTriggered();}, this->iController.meta, "sensorTriggered");};
  iTimer.out.timeout = [&](){return dzn::call_out(this,[=]{ return iTimer_timeout();}, this->iTimer.meta, "timeout");};





}

void Controller::iController_passwordEnterred(std::string pwd)
{
  if ((state == ::Controller::State::Unarmed && true)) 
  {
    bool valid = this->iPwdManager.in.verifyPassword(pwd);
    {
      if (valid) 
      {
        state = ::Controller::State::Armed;
        this->iLed.in.setYellow();
      }
    }
  }
  else if ((state == ::Controller::State::Armed && true)) 
  {
    bool valid = this->iPwdManager.in.verifyPassword(pwd);
    {
      if (valid) 
      {
        state = ::Controller::State::Unarmed;
        this->iLed.in.setGreen();
      }
    }
  }
  else if ((state == ::Controller::State::Alarming && true)) 
  {
    bool valid = this->iPwdManager.in.verifyPassword(pwd);
    {
      if (valid) 
      {
        state = ::Controller::State::Armed;
        this->iLed.in.setYellow();
        this->iSiren.in.turnOff();
        this->iTimer.in.cancel();
      }
    }
  }
  else if ((!((state == ::Controller::State::Alarming && true)) && (!((state == ::Controller::State::Armed && true)) && (!((state == ::Controller::State::Unarmed && true)) && true)))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void Controller::iController_sensorTriggered()
{
  if ((state == ::Controller::State::Unarmed && true)) ;
  else if ((state == ::Controller::State::Armed && true)) 
  {
    state = ::Controller::State::Alarming;
    this->iTimer.in.start(30000);
    this->iLed.in.setRed();
  }
  else if ((state == ::Controller::State::Alarming && true)) ;
  else if ((!((state == ::Controller::State::Alarming && true)) && (!((state == ::Controller::State::Armed && true)) && (!((state == ::Controller::State::Unarmed && true)) && true)))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void Controller::iTimer_timeout()
{
  if ((state == ::Controller::State::Unarmed && true)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else if ((state == ::Controller::State::Armed && true)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else if ((state == ::Controller::State::Alarming && true)) 
  {
    this->iSiren.in.turnOn();
  }
  else if ((!((state == ::Controller::State::Alarming && true)) && (!((state == ::Controller::State::Armed && true)) && (!((state == ::Controller::State::Unarmed && true)) && true)))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}


void Controller::check_bindings() const
{
  dzn::check_bindings(&dzn_meta);
}
void Controller::dump_tree(std::ostream& os) const
{
  dzn::dump_tree(os, &dzn_meta);
}




//version: 2.8.2