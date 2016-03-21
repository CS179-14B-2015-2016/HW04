#ifndef PLAYERSHOOT_H_INCLUDED
#define PLAYERSHOOT_H_INCLUDED

#include "ShootBehavior.h"

class BulletStage;
class PlayerShoot: public ShootBehavior {
public:
    void operator() (BulletStage* stage, vec2f position) override;
    static PlayerShoot getInstance();

};

#endif // PLAYERSHOOT_H_INCLUDED
