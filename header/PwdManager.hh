#include "IPwdManager.hh"

class PwdManager : public skel::PwdManager {
    bool iPwdManager_verifyPassword (std::string pwd);

public:
    PwdManager(const dzn::locator& loc);

};