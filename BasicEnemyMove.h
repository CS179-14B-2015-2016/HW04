#ifndef BASICENEMYMOVE_H_INCLUDED
#define BASICENEMYMOVE_H_INCLUDED

#include "MoveBehavior.h"
#include "Vector2Plus.h"

class BasicEnemyMove: public MoveBehavior {
private:
    float wait;
    vec2f direction;
    float time;
public:
    BasicEnemyMove(): wait(0), direction(vec2f(1, 0)), time(3) {}
    static BasicEnemyMove getInstance();
    void operator() (Entity* ent, float dt) override;
};


#endif // BASICENEMYMOVE_H_INCLUDED
