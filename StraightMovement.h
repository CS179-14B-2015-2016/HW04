#ifndef STRAIGHTMOVEMENT_H_INCLUDED
#define STRAIGHTMOVEMENT_H_INCLUDED

#include "MoveBehavior.h"
class StraightMovement: public MoveBehavior {
public:
    static StraightMovement getInstance();
    void operator() (Entity* ent, float dt) override;
};

#endif // STRAIGHTMOVEMENT_H_INCLUDED
