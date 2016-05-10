#include "StateManager.h"

void State::popSelf(unsigned int level, std::string pass)
{
    sm->pop(level, pass);
}
