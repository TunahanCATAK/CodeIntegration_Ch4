#include "PwdManager.hh"

#include <iostream>
#include <string>

PwdManager::PwdManager(const dzn::locator &loc) : skel::PwdManager(loc){
    std::cout << "PwdManager is constructed." << std::endl;
}

bool PwdManager::iPwdManager_verifyPassword(std::string pwd) {
    return (pwd.compare(this->Pass) == 0);
}