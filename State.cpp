#include "StateManager.h"
#include <iostream>

void State::popSelf(unsigned int level, std::string pass)
{
    sm->pop(level, pass);
}
