#include "StraightMovement.h"
#include "Vector2Plus.h"
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <iostream>

StraightMovement StraightMovement::getInstance() {
    static StraightMovement move;
    return move;
}

void StraightMovement::operator() (Entity* ent, float dt) {
    vec2f displacement = ent->getDirection();
    displacement /= mag(displacement);
    float distance = ent->getSpeed();
    distance *= dt;
    displacement *= distance;

    vec2f position = ent->getPosition() + displacement;
    ent->setPosition(position);
}
