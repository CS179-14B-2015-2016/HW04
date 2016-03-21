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
    float counter;
    bool isWaiting,first;
    BasicEnemyMove(): wait(0), direction(vec2f(1, 0)),counter(0) , time(3),isWaiting(false),first(true){}
    static BasicEnemyMove getInstance();
    void operator() (Entity* ent, float dt) override;
    //void operator() (Entity* ent, Entity* player, float dt) override;
};


#endif // BASICENEMYMOVE_H_INCLUDED
