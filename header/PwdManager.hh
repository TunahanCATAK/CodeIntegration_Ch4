#include "IPwdManager.hh"

#include <string>

class PwdManager : public skel::PwdManager {

    const std::string Pass = "1234";
    bool iPwdManager_verifyPassword (std::string pwd);

public:
    PwdManager(const dzn::locator& loc);

};