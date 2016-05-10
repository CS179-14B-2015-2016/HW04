#ifndef SIMPLEENEMYMOVEMENT_H_INCLUDED
#define SIMPLEENEMYMOVEMENT_H_INCLUDED

#include "MoveBehavior.h"
#include "Vector2Plus.h"

class SimpleEnemyMovement: public MoveBehavior {
private:
    float wait;
    vec2f direction;
    float time;
    int turn = 0;
    int ctr = 0;
public:
    SimpleEnemyMovement(): wait(0), direction(vec2f(-30, 321)), time(3) {}
    static SimpleEnemyMovement getInstance();
    void operator() (Entity* ent, float dt) override;
};



#endif // SIMPLEENEMYMOVEMENT_H_INCLUDED
