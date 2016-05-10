#ifndef PLAYERMOVE_H_INCLUDED
#define PLAYERMOVE_H_INCLUDED

#include "MoveBehavior.h"

class PlayerMove: public MoveBehavior {
public:
    static PlayerMove getInstance();
    void operator() (Entity* ent, float dt) override;
};

#endif // PLAYERMOVE_H_INCLUDED
