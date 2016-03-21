#ifndef SHOOTBEHAVIOR_H_INCLUDED
#define SHOOTBEHAVIOR_H_INCLUDED

class BulletStage;
class ShootBehavior {
public:
    virtual void operator() (BulletStage* stage, vec2f position) = 0;
};

#endif // SHOOTBEHAVIOR_H_INCLUDED
