#include "BasicEnemyMove.h"
#include "Vector2Plus.h"
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <iostream>
#include <algorithm>

BasicEnemyMove BasicEnemyMove::getInstance() {
    static BasicEnemyMove move;
    return move;
}

void BasicEnemyMove::operator() (Entity* ent, float dt) {
    if(wait>0) {
        wait = std::max(0.0f, wait-dt);
        if(wait==0)
            time = 6;
    }
    else if (time>0) {
        vec2f orig = ent->getPosition();
        orig += ent->getSpeed()*dt*direction;
        ent->setPosition(orig);
        time = std::max(0.0f, time-dt);
        if(time==0)
        {
            wait = 5;
            direction = direction*-1.0f;
        }
    }
}
