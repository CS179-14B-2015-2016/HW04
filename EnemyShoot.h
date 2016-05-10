#ifndef ENEMYSHOOT_H_INCLUDED
#define ENEMYSHOOT_H_INCLUDED

#include "ShootBehavior.h"

class BulletStage;
class EnemyShoot: public ShootBehavior {
private:
    float greenPos;
    float bluePos;
    float dt;
public:
    EnemyShoot(float dt): greenPos(0), bluePos(360), dt(dt) {}
    void operator() (BulletStage* stage, vec2f position) override;
    static EnemyShoot getInstance(float dt);

};

#endif // ENEMYSHOOT_H_INCLUDED
