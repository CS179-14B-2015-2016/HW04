#ifndef SIMPLEENEMYSHOOT_H_INCLUDED
#define SIMPLEENEMYSHOOT_H_INCLUDED
#include "ShootBehavior.h"

class BulletStage;
class SimpleEnemyShoot: public ShootBehavior {
private:
    float greenPos;
    float bluePos;
    float dt;
public:
    SimpleEnemyShoot(float dt): greenPos(0), bluePos(360), dt(dt) {}
    void operator() (BulletStage* stage, vec2f position) override;
    static SimpleEnemyShoot getInstance(float dt);
    static vec2f* circleShot(vec2f, vec2f);
};
#endif // SIMPLEENEMYSHOOT_H_INCLUDED
